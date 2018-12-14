/*
 *   This file is a part of the OpenPhase software project.
 *   For more details visit www.openphase.de
 *
 *   Created:    2015
 *
 *   Authors:    Efim Borukhovich; Johannes G�rler
 *
 *   Copyright (c) 2009-2017 Interdisciplinary Centre for Advanced Materials
 *                 Simulation (ICAMS). Ruhr-Universitaet Bochum. Germany
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Mechanics/Storages/PlasticProperties.h"
#include "Tools.h"
#include "Settings.h"
#include "InterfaceEnergy.h"
#include "InterfaceMobility.h"
#include "DoubleObstacle.h"
#include "PhaseField.h"
#include "DrivingForce.h"
#include "Initializations.h"
#include "BoundaryConditions.h"
#include "Mechanics/Storages/ElasticProperties.h"
#include "Mechanics/ElasticityModels/ElasticityKhachaturyan.h"
#include "Mechanics/ElasticitySolvers/ElasticitySolverSpectral.h"
#include "Velocities.h"
#include "Mechanics/LargeDeformations/LargeDeformations.h"
#include "Orientations.h"
#include "Base/Quaternion.h"
#include "Mechanics/Storages/DamageProperties.h"
#include "Mechanics/DamageModels/DamageModel.h"
#include "Mechanics/PlasticFlow/PlasticFlowCP.h"
#include "TextOutput.h"
#include "VTK.h"

//#define damagemodel

using namespace std;
using namespace openphase;

/************************************main**************************************/
int main(int argc, char *argv[])
{
    Settings                        OPSettings;
    PhaseField                      Phi;
    DoubleObstacle                  DO;
    InterfaceMobilityIdentical      Mu;
    InterfaceEnergyAnisotropic      Sigma;
    DrivingForce                    dG;
    BoundaryConditions              BC;
    ElasticProperties               EP;
    ElasticityKhachaturyan          EM;
#ifdef damagemodel
    DamageProperties                DP;
    DamageModel                     DM;
#endif
    PlasticProperties				PFP;
    PlasticFlowCP                   PFCP;

    OPSettings.Initialize();
    OPSettings.ReadInput();

    EP.Initialize(OPSettings);
    EP.ReadInput(ProjectInputDir + "ElasticInput.opi");

    Orientations                    OR(OPSettings);
    Velocities                      Vel(OPSettings);
    ElasticitySolverSpectral        ES(OPSettings);
    LargeDeformations               LD(OPSettings, EP);


    vector<OPObject*> PresentObjects;

    PresentObjects.push_back(&Phi);
    PresentObjects.push_back(&DO);
    PresentObjects.push_back(&Mu);
    PresentObjects.push_back(&Sigma);
    PresentObjects.push_back(&dG);
    PresentObjects.push_back(&BC);
    PresentObjects.push_back(&EP);
    PresentObjects.push_back(&EM);
    PresentObjects.push_back(&LD);
    PresentObjects.push_back(&Vel);
    PresentObjects.push_back(&OR);
    PresentObjects.push_back(&ES);
//    PresentObjects.push_back(&CP);
//    PresentObjects.push_back(&CM);
#ifdef damagemodel
    PresentObjects.push_back(&DP);
    PresentObjects.push_back(&DM);
#endif
    PresentObjects.push_back(&PFP);
    PresentObjects.push_back(&PFCP);

    BC.Initialize(OPSettings);
    Mu.Initialize(OPSettings);
    Sigma.Initialize(OPSettings);
    Phi.Initialize(OPSettings);
    dG.Initialize(OPSettings);
    DO.Initialize(OPSettings);
    EM.Initialize(OPSettings);
//    CP.Initialize(OPSettings, Phi);
//    CM.Initialize(OPSettings);
    PFP.Initialize(OPSettings);
    PFCP.Initialize(OPSettings);
#ifdef damagemodel
    DP.Initialize(OPSettings, EP, ProjectInputDir + "DamageInput.opi");
    DM.Initialize(OPSettings);
    DM.ReadInput();
#endif

    BC.ReadInput();
    PFCP.ReadInput(ProjectInputDir + "PlasticFlowInput.opi");
    OR.ReadInput(ProjectInputDir + "OrientationsInput.opi");

    if(OPSettings.Restart)
    {
        cout << "Restart data being read!";
        Phi.Read(BC, OPSettings.tStart);
		OR.SetRandomGrainOrientations(Phi, 0);
        EP.SetGrainsProperties(Phi);
        OPSettings.tStart -= 1;
        cout << " Done!" << endl;
    }
    else
    {
        OPSettings.tStart = -1;

        int number_of_grains = 25;
        Initializations::VoronoiTesselation(Phi, BC, OPSettings, number_of_grains, 1);
        for(int tStepini = 0; tStepini < 50; tStepini++)
        {
            Sigma.CalculateCubic(Phi);
            DO.CalculatePhaseFieldIncrements(Phi, Sigma, Mu);
            Phi.NormalizeIncrements(BC, 0.0001);
            Phi.MergeIncrements(BC, 0.0001);
        }

//        Initializations::Single(Phi, 1, BC, OPSettings);
//        Initializations::Fractional(Phi, 2, 1, 16, BC, OPSettings);
//        Initializations::Sphere(Phi, 2, 5, 16, 0, 16, BC, OPSettings);
        OR.SetRandomGrainOrientations(Phi, 0);
//        GenerateGrainAngles(Phi, OR);
        EP.SetGrainsProperties(Phi);
        cout << "Initialization stage! Done!\n" << endl;
    }

#ifdef composition
    PFCP.SetInitialHardening(Phi, Cx, BC);
#else
    PFCP.SetInitialHardening(Phi, BC);
#endif
    cout << "Entering the Time Loop!!!" << endl;
    remove("avgStress.dat");
    remove("avgStrain.dat");
    TextOutput::AverageStress(EP, "avgStress.dat", 0.0);
    //-------------- The Time Loop -------------//
    for(int tStep = OPSettings.tStart + 1; tStep < OPSettings.tStart + OPSettings.nSteps+1; tStep++)
    {
        EP.AppliedStrain[2] += 0.0005;
//        EP.AppliedStrain[0] = -0.3*EP.AppliedStrain[2];
//        EP.AppliedStrain[1] = -0.3*EP.AppliedStrain[2];

//        EP.AppliedStrain[2] += 0.0005;
//        EP.AppliedStrain[0] = sqrt(1./(1.0 + EP.AppliedStrain[2])) - 1.0;
//        EP.AppliedStrain[1] = EP.AppliedStrain[0];

        LD.Solve(PresentObjects, OPSettings.dt, !(tStep%OPSettings.tScreenWrite));

        if (!(tStep%OPSettings.tRestartWrite))
        {
            Phi.Write(tStep);
            OR.Write(tStep);
        }

        if (!(tStep%OPSettings.tFileWrite))
        {
            Phi.WriteVTK(tStep);
            EP.WriteStressesVTK(tStep);
            EP.WriteEffectiveEigenStrainsVoigtVTK(tStep);
            OR.WriteTotalVTK(Phi, tStep);
            PFP.WritePlasticStrainVTK(tStep);
            EP.WriteStrainsVTK(tStep);
            PFCP.WriteCRSSVTK(Phi, tStep);
#ifdef composition
            Cx.WriteVTK(tStep);
#endif
#ifdef damagemodel
            DP.WriteEffectiveDamageVTK(tStep);
            DM.WriteVTK(tStep);
#endif
        }

        if (!(tStep%OPSettings.tScreenWrite))
        {
            time_t rawtime;
            time(&rawtime);
            double simtime = tStep*OPSettings.dt;
            cout<<"timestep/nSteps: "<<tStep<<"/"<<OPSettings.tStart + OPSettings.nSteps<<endl;
            cout << "++++++++++++++++++++++++++++++++++++++++++++\n"
                 << "============================================\n"
                 << "Time Step        : " << tStep << "\n"
                 << "Simulation Time  : " << simtime << " s\n"
                 << "Wall Clock Time  : " << ctime(&rawtime);
            cout << "============================================\n" << endl;
        }
        TextOutput::AverageStress(EP, "avgStress.dat", fabs(EP.AppliedStrain.Ln()[2]));
        TextOutput::AverageStrain(PFP.PlasticStrain, "avgStrain.dat", tStep);
        if (!(tStep%10))
        {
            int systemReturn = system("gnuplot StressStrain.plot");
            if(systemReturn == -1)
            {
              // The system method failed
            }
        }
    } //end time loop
   return 0;
}