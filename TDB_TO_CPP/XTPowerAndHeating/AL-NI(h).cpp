#include <vector>
void printerror(double T)
{
    exit(0);
}
const double precision = 1E-6;
const double R = 8.3144521;
double dummy(std::vector<double>& a, double b, double c)
{
    return 0.0;
}
/**************************************************************************
***************************************************************************
A) Definition of elements
From A. T. Dinsdale, SGTE data for pure elements (REF 0)

***************************************************************************
Element        	Standard     	state          	mass [g/mol]   	enthalpy_298   	entropy_298    
ELEMENT        	/-             	ELECTRON_GAS   	0.0000E+00     	0.0000E+00     	0.0000E+00!    	
ELEMENT        	VA             	VACUUM         	0.0000E+00     	0.0000E+00     	0.0000E+00!    	
ELEMENT        	AL             	FCC_A1         	2.6982E+01     	4.5773E+03     	2.8322E+01!    	
ELEMENT        	NI             	FCC_A1         	5.8690E+01     	4.7870E+03     	2.9797E+01!    	
***************************************************************************
C) Gibbs energy functions
***************************************************************************
###########################################################
SER (Standard elements references)
###########################################################*/

double GHSERAL (double T) {
    double val = 0.0;
    if(T < 298.14 or T > 2900) { printerror(T); }
    else if(T >= 298.14 and T < 700) {
        val = -7976.15+137.093038*T-24.3671976*T*LN(T)-.001884662*T**2-8.77664E-07*T**3+74092*T**(-1); }
    else if(T >= 700 and T < 933.47) {
        val = Y-11276.24+223.048446*T-38.5844296*T*LN(T)+.018531982*T**2-5.764227E-06*T**3+74092*T**(-1); }
    else if(T >= 933.47 and T < 2900) {
        val = Y-11278.378+188.684153*T-31.748192*T*LN(T)-1.230524E+28*T**(-9); }
    return val; }

double GHSERNI (double T) {
    double val = 0.0;
    if(T < 298.14 or T > 6000) { printerror(T); }
    else if(T >= 298.14 and T < 1728) {
        val = -5179.159+117.854*T-22.096*T*LN(T)-.0048407*T**2; }
    else if(T >= 1728 and T < 6000) {
        val = Y-27840.655+279.135*T-43.1*T*LN(T)+1.12754E+31*T**(-9); }
    return val; }

/*******************************************************
                        FUNCTIONS
********************************************************/

double GLIQAL (double T) {
    double val = 0.0;
    if(T < 298.14 or T > 6000) { printerror(T); }
    else if(T >= 298.14 and T < 933.47) {
        val = +11005.029-11.841867*T+7.934E-20*T**7+GHSERAL#; }
    else if(T >= 933.47 and T < 6000) {
        val = Y+10482.382-11.253974*T+1.231E+28*T**(-9)+GHSERAL#; }
    return val; }

double GLIQNI (double T) {
    double val = 0.0;
    if(T < 298.14 or T > 6000) { printerror(T); }
    else if(T >= 298.14 and T < 1728) {
        val = +16414.686-9.397*T-3.82318E-21*T**7+GHSERNI#; }
    else if(T >= 1728 and T < 6000) {
        val = Y+18290.88-10.537*T-1.12754E+31*T**(-9)+GHSERNI#; }
    return val; }

double UALNI (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = -14808.6667+2.9307*T; }
    return val; }

double LALNI0 (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = +0.0; }
    return val; }

double LALNI1 (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = +7204-3.743*T; }
    return val; }

double GBCCAL (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = +10083-4.813*T+GHSERAL#; }
    return val; }

double GBCCNI (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = +8715.084-3.556*T+GHSERNI#; }
    return val; }

double GB2ALVA (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = +10000-T; }
    return val; }

double LB2ALVA (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = +150000; }
    return val; }

double GB2NIVA (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = +162397.3-27.40575*T; }
    return val; }

double LB2NIVA (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = -64024.38+26.49419*T; }
    return val; }

double GB2ALNI (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = -152397.3+26.40575*T; }
    return val; }

double LB2ALNI (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 6000) { printerror(T); }
    else if(T >= 298.15 and T < 6000) {
        val = -52440.88+11.30117*T; }
    return val; }

double UN_ASS (double T) {
    double val = 0.0;
    if(T < 298.15 or T > 300) { printerror(T); }
    else if(T >= 298.15 and T < 300) {
        val = +0; }
    return val; }
/*#######################################################################
 PHASE AL3NI  %  2 .75   .25 !
     CONSTITUENT AL3NI  :AL : NI :  !
-------------------------------------------------------------------
AL3NI endmember compounds with VA 
-------------------------------------------------------------------*/
double  G_AL3NI__AL_NI_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -48483.73+12.29913*T+.75*GHSERAL#+.25*GHSERNI#;  } 

//**************** Gibbs Energy of AL3NI  *********************

/*#######################################################################
 PHASE AL3NI2  %  3 3   2   1 !
     CONSTITUENT AL3NI2  :AL : AL,NI% : NI,VA% :  !
-------------------------------------------------------------------
AL3NI2 endmember compounds with VA 
-------------------------------------------------------------------*/
double  G_AL3NI2__AL_AL_NI_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -39465.978+7.89525*T+5*GBCCAL#+GBCCNI#;  } 

double  G_AL3NI2__AL_NI_NI_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -427191.9+79.21725*T+3*GBCCAL#+3*GBCCNI#;  } 

double  G_AL3NI2__AL_AL_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +30000-3*T+5*GBCCAL#;  } 

double  G_AL3NI2__AL_NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -357725.92+68.322*T+3*GBCCAL#+2*GBCCNI#;  } 

double  G_AL3NI2__AL_AL__NI_NI_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -193484.18+131.79*T;  } 

double  G_AL3NI2__AL_AL_NI__VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -22001.7+7.0332*T;  } 

double  G_AL3NI2__AL_NI_NI__VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -22001.7+7.0332*T;  } 

double  G_AL3NI2__AL_AL__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -193484.18+131.79*T;  } 

//**************** Gibbs Energy of AL3NI2  *********************

/*#######################################################################
 PHASE AL3NI5  %  2 .375   .625 !
     CONSTITUENT AL3NI5  :AL : NI :  !
-------------------------------------------------------------------
AL3NI5 endmember compounds with VA 
-------------------------------------------------------------------*/
double  G_AL3NI5__AL_NI_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -55507.7594+7.2648103*T+.375*GHSERAL#+.625*GHSERNI#;  } 

//**************** Gibbs Energy of AL3NI5  *********************

/*#######################################################################
 TYPE_DEFINITION & GES A_P_D BCC_A2 MAGNETIC  -1.0    4.00000E-01 !
 PHASE BCC_A2  %&  2 1   3 !
     CONSTITUENT BCC_A2  :AL,NI,VA : VA :  !
-------------------------------------------------------------------
BCC_A2 endmember compounds with VA 
-------------------------------------------------------------------*/
double  G_BCC_A2__AL_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GBCCAL#;  } 

double  G_BCC_A2__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GBCCNI#;  } 

double  TC_BCC_A2__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +575;  } 

double  BMAGN_BCC_A2__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +.85;  } 

double  G_BCC_A2__VA_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +0.0;  } 

double  G_BCC_A2__AL__VA_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GB2ALVA#+LB2ALVA#;  } 

double  G_BCC_A2__AL__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GB2ALNI#+LB2ALNI#;  } 

double  G_BCC_A2__NI__VA_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GB2NIVA#+LB2NIVA#;  } 

//**************** Gibbs Energy of BCC_A2  *********************

/*#######################################################################
$ THIS PHASE HAS A DISORDERED CONTRIBUTION FROM BCC_A2                  
 TYPE_DEFINITION ' GES AMEND_PHASE_DESCRIPTION BCC_B2 DIS_PART BCC_A2,,,!
 PHASE BCC_B2  %'  3 .5   .5   3 !
     CONSTITUENT BCC_B2  :AL%,NI,VA : AL,NI%,VA : VA :  !
-------------------------------------------------------------------
BCC_B2 endmember compounds with VA 
-------------------------------------------------------------------*/
double  G_BCC_B2__AL_AL_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +0.0;  } 

double  G_BCC_B2__NI_AL_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +.5*GB2ALNI#-.5*LB2ALNI#;  } 

double  G_BCC_B2__VA_AL_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +.5*GB2ALVA#-.5*LB2ALVA#;  } 

double  G_BCC_B2__AL_NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +.5*GB2ALNI#-.5*LB2ALNI#;  } 

double  G_BCC_B2__NI_NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +0.0;  } 

double  G_BCC_B2__VA_NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +.5*GB2NIVA#-.5*LB2NIVA#;  } 

double  G_BCC_B2__AL_VA_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +.5*GB2ALVA#-.5*LB2ALVA#;  } 

double  G_BCC_B2__NI_VA_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +.5*GB2NIVA#-.5*LB2NIVA#;  } 

double  G_BCC_B2__VA_VA_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +0.0;  } 

//**************** Gibbs Energy of BCC_B2  *********************

/*#######################################################################
 TYPE_DEFINITION ( GES A_P_D FCC_A1 MAGNETIC  -3.0    2.80000E-01 !
 PHASE FCC_A1  %(  2 1   1 !
     CONSTITUENT FCC_A1  :AL,NI : VA :  !
-------------------------------------------------------------------
FCC_A1 endmember compounds with VA 
-------------------------------------------------------------------*/
double  G_FCC_A1__AL_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GHSERAL#;  } 

double  G_FCC_A1__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GHSERNI#;  } 

double  TC_FCC_A1__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +633;  } 

double  BMAGN_FCC_A1__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +.52;  } 

double  G_FCC_A1__AL__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -162407.75+16.212965*T;  } 

double  G_FCC_A1__AL__NI_VA_1 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +73417.798-34.914168*T;  } 

double  G_FCC_A1__AL__NI_VA_2 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +33471.014-9.8373558*T;  } 

double  G_FCC_A1__AL__NI_VA_3 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -30758.01+10.25267*T;  } 

//**************** Gibbs Energy of FCC_A1  *********************

/*#######################################################################
$ THIS PHASE HAS A DISORDERED CONTRIBUTION FROM FCC_A1                  
 TYPE_DEFINITION ) GES AMEND_PHASE_DESCRIPTION L12 DIS_PART FCC_A1,,,!
 PHASE L12  %)  3 .75   .25   1 !
     CONSTITUENT L12  :AL,NI% : AL%,NI : VA% :  !
-------------------------------------------------------------------
L12 endmember compounds with VA 
-------------------------------------------------------------------*/
double  G_L12__AL_AL_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +0.0;  } 

double  G_L12__NI_AL_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +3*UALNI#;  } 

double  G_L12__AL_NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +3*UALNI#;  } 

double  G_L12__NI_NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +0.0;  } 

double  G_L12__*_AL__NI_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +LALNI0#;  } 

double  G_L12__*_AL__NI_VA_1 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +LALNI1#;  } 

double  G_L12__AL__NI_*_VA_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +6*UALNI#+3*LALNI0#;  } 

double  G_L12__AL__NI_*_VA_1 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +3*LALNI1#;  } 

//**************** Gibbs Energy of L12  *********************

/*#######################################################################
 PHASE LIQUID  %  1  1.0  !
     CONSTITUENT LIQUID  :AL,NI :  !
-------------------------------------------------------------------
LIQUID endmember compounds with VA 
-------------------------------------------------------------------*/
double  G_LIQUID__AL_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GLIQAL#;  } 

double  G_LIQUID__NI_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +GLIQNI#;  } 

double  G_LIQUID__AL__NI_0 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -207109.28+41.31501*T;  } 

double  G_LIQUID__AL__NI_1 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -10185.79+5.8714*T;  } 

double  G_LIQUID__AL__NI_2 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +81204.81-31.95713*T;  } 

double  G_LIQUID__AL__NI_3 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return +4365.35-2.51632*T;  } 

double  G_LIQUID__AL__NI_4 (double T) {  
	 if ( T < 298.15 or T > 6000) { printerror(T); } 
	 return -22101.64+13.16341*T;  } 

//**************** Gibbs Energy of LIQUID  *********************
