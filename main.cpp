#include "TROOT.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TDatime.h"
#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include <iostream>

double PhiDistribution(double x)
{
  double              v1       = 0.02;
  double              v2       = 0.25;
  double              PsiRP    = 30 * TMath::Pi()/180;
  
  return ( 1 + 2*v1*TMath::Cos(x-PsiRP) + 2*v2*TMath::Cos(2*(x-PsiRP)) );
}

int main()
{
  double PhiDistribution(double x);
  const unsigned int  Nevents  = 10000;
  
  TH1F*     hTheta            = new TH1F("hTheta","#theta angle distribution;#theta;N_{evts}",100,0.,TMath::Pi());
  TH1F*     hPhi              = new TH1F("hPhi","#phi angle distribution;#phi;N_{evts}",100,-TMath::Pi(),TMath::Pi());
  TDatime*  tNow              = new TDatime();
  TRandom3* rNumber           = new TRandom3(tNow->GetTime());
  TF1*      fPhiDistribution  = new TF1("fPhiDistribution","PhiDistribution(x)",-TMath::Pi(),TMath::Pi());
  
  for (unsigned int i=0;i<Nevents;i++){
    hTheta->Fill(TMath::ACos((rNumber->Rndm()-0.5)*2));
    hPhi  ->Fill(fPhiDistribution->GetRandom());
  }
  
  TCanvas *canv = new TCanvas("canv","Distributions",1280,720);
  canv -> Divide(3,1);
  
  canv->cd(1);
  fPhiDistribution->Draw();
  canv->cd(2);
  hTheta->Draw();
  canv->cd(3);
  hPhi->Draw();
  return 0;
}
