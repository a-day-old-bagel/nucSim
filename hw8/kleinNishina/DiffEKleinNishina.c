/*
A program to calculate the Energy Differential Compton Scattering  
Crosssection (d Sigma/ dE)
in units of barns  using the Klein-Nachina formula.
pass electron min kinetic energy, Photon Energy and step size (Emin,Egamma,Estep)
*/
/* system include files for input and output*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
main(int argc, char *argv[])
{
  int i,loop;
  int Emin,Estep,Egamma;
  double Emax,Eelectron,PI,DSigma_DE,R,Bohr_Radius_sqrd,Eo_electron,s,psi;
  PI=3.1415927;
  Bohr_Radius_sqrd=2.817e-13*2.817e-13/1e-24;/*barns*/
  if(argc==4)
    {
/* convert the comand line string to an integer*/
      Emin=atoi(argv[1]); 
      Egamma=atoi(argv[2]);
      Estep=atoi(argv[3]); 
    }
  else
    {
      fprintf(stderr,"Error you must enter 3 energies in eV on the comand line\n");
      fprintf(stderr,"usage: DiffEXsect [electron min KE] [Incident photon E] [elecron KE step size]\n");
      exit(1);
    }
  Eo_electron=511000; /* rest mass of electronin eV */
  psi=Egamma/Eo_electron;
  Emax=Egamma*2*psi/(1+2*psi);  /* compton edge */
  fprintf(stderr,"Calculating Differential Compton cross section (in barns/eV) for \n\t %d < E < %g in steps of %d and %d eV incident Photons\n",Emin,Emax,Estep,Egamma);
 Eelectron=Emin-Estep;
 for(i=Emin;i<=Emax; i+=Estep)
   {
     Eelectron+=Estep;
     /*      fprintf(stderr,"Eelectron=%g\n",Eelectron);*/
     s=Eelectron/Egamma;
     DSigma_DE=s*(s-2/psi)/(1-s);
     DSigma_DE=DSigma_DE+s*s/(1-s)/(1-s)/psi/psi;
     DSigma_DE=2.0+DSigma_DE;
     DSigma_DE=PI*Bohr_Radius_sqrd*DSigma_DE/Eo_electron/psi/psi;
     fprintf(stdout,"%g\t%g\n",Eelectron,DSigma_DE);
   }
}