// compare FormulaEvaluator with TFormula
// Author: A.Karavdina
// Date: 30.07.2018
// run it (with CMSSW env 94X and above):
// root -l -b -q fevaltest_Residuals.C
#include "CondFormats/JetMETObjects/interface/SimpleJetCorrector.h"

void fevaltest_Residuals() {
  gStyle->SetOptStat(0);                                                                      
  gStyle->SetTitleSize(0.045,"x");                                                                                                                                    
  gStyle->SetTitleSize(0.045,"y");                                                                                                                                    
  gStyle->SetTitleYOffset(0.9);  

  gSystem->Load("libFWCoreFWLite.so");
  FWLiteEnabler::enable();


  //TString formula = "[2]*([3]*([4]+[5]*TMath::Log(max([0],min([1],x))))*1./([6]+[7]*100./3.*(TMath::Max(0.,1.03091-0.051154*pow(x,-0.154227))-TMath::Max(0.,1.03091-0.051154*TMath::Power(208.,-0.154227)))+[8]*0.021*(-1.+1./(1.+exp(-(TMath::Log(x)-5.030)/0.395)))))";//Fall17_17Nov2017F_V8_DATA_L2L3Residual_AK4PFchs
  //TString formula = "[2]*([3]*([4]+[5]*TMath::Log(max([0],min([1],x))))*1./([6]+[7]*100./3.*(TMath::Max(0.,1.03091-0.051154*TMath::Power(x,-0.154227))-TMath::Max(0.,1.03091-0.051154*TMath::Power(208.,-0.154227)))+[8]*((1-(3.906-1.652*TMath::Log(x)+0.2257*TMath::Power(TMath::Log(x),2))/x)-(1-(3.906-1.652*TMath::Log(208.)+0.2257*TMath::Power(TMath::Log(208.),2))/208.))))";//L2L3Res Summer16_07Aug_V17
  TString formula = "[2]*([3]*([4]+[5]*TMath::Log(max([0],min([1],x))))*1./([6]+[7]*(100./3.)*(TMath::Max(0.,1.03091-0.051154*TMath::Power(x,-0.154227))-TMath::Max(0.,1.03091-0.051154*TMath::Power(208.,-0.154227)))+[8]*((1-(1./x)*(3.906-1.652*TMath::Log(x)+0.2257*TMath::Power(TMath::Log(x),2)))-(1-(1./208.)*(3.906-1.652*TMath::Log(208.)+0.2257*TMath::Power(TMath::Log(208.),2))))))";//L2L3Res Summer16_07Aug_V17



  TString region[3] ={"barrel","endcap","forward"};
  TMultiGraph *mg = new TMultiGraph();
  TGraph *gr[3];
  TLegend *legend=new TLegend(0.15,0.65,0.88,0.87);
  //  TLegend *legend=new TLegend(0.15,0.65,0.89,0.87);
  legend->SetTextFont(72);
  legend->SetTextSize(0.045);
  legend->SetFillColor(0);
  //  legend->SetHeader("Summer16_07Aug2017BCD_V11_DATA_L1FastJet_AK4PFchs");
  //  legend->SetHeader("Summer16_07Aug2017_V11");
  //legend->SetHeader("Summer16_07Aug2017_V11_AK8CHS");
  //  legend->SetHeader("Summer16_07Aug2017_V11_fix");
  //legend->SetHeader("Fall17_17Nov2017_V20");
  //    legend->SetHeader("Summer16_07Aug2017GH_V11_L2L3Res");
  //    legend->SetHeader("Fall17_17Nov2017F_V8_DATA_L2L3Res");
  legend->SetHeader("Summer16_07Aug2017_V17");

  for(int r=0;r<3;r++){
    //std::cout<<region[r]<<std::endl;
    gr[r] = new TGraph(); 
    gr[r]->SetLineColor(r+1);  gr[r]->SetMarkerColor(r+1); gr[r]->SetLineWidth(4-r);
    //    double par[3];
    double par[9];
    if(r==0){//barrel
      double par_tmp[] = {30, 1310, 1.000159, 0.999957, 0.974947, 0.004438, 0.9851, 0.1604, -2.268};
      for (int i=0;i<9;i++)
	par[i] = par_tmp[i];
    }
    if(r==1){//endcap
      double par_tmp[] = {30, 690, 1.000159, 1.000519, 1.049185, -0.010140, 0.9851, 0.1604, -2.268};
      for (int i=0;i<9;i++)
	par[i] = par_tmp[i];
    }
    if(r==2){//forward
      double par_tmp[] = {30, 200, 1.000159, 1.000627, 1.012743, -0.005450, 0.9851, 0.1604, -2.268};
      for (int i=0;i<9;i++)
	par[i] = par_tmp[i];
    }

    double pt[17]={15,17,20,30,40,50,60,70,80,90,100,200,400,600,800,1000,2000};
    //double pt[1]={100};
    //  for(int i=0;i<1;i++){
    for(int i=0;i<17;i++){
      double x[1] = {pt[i]};//AK4CHS

    //    double par[3] = { 1.4, 0.453645, -0.015665 };

  reco::FormulaEvaluator mFunc(formula.Data());
  //  float fe = mFunc.evaluate(reco::formula::ArrayAdaptor(x,3), reco::formula::ArrayAdaptor(par,3) );
  //  float fe = mFunc.evaluate(reco::formula::ArrayAdaptor(x,3), reco::formula::ArrayAdaptor(par,6) );
  float fe = mFunc.evaluate(reco::formula::ArrayAdaptor(x,9), reco::formula::ArrayAdaptor(par,9) );
  std::cout <<  "fe: " << fe <<  std::endl;

  TFormula f1("f1",formula);
  f1.SetParameter(0, par[0]);
  f1.SetParameter(1, par[1]);
  f1.SetParameter(2, par[2]);
  f1.SetParameter(3, par[3]);
  f1.SetParameter(4, par[4]);
  f1.SetParameter(5, par[5]);
  f1.SetParameter(6, par[6]);
  f1.SetParameter(7, par[7]);
  f1.SetParameter(8, par[8]);


  //  float tf = f1.Eval(x[0],x[1],x[2]);
  float tf = f1.Eval(x[0]);
  std::cout <<  "tf: " << tf <<  std::endl;


  gr[r]->SetPoint(i,pt[i],(tf-fe)/tf);
  // TString formula_forpy = "max(0.0001,1-[y]*([1]*([z]-[0])*(1+[2]*__import__('math').log([x]/30.)))/[x])";
  // formula_forpy = formula_forpy.ReplaceAll("[x]","157.2") \
  //   .ReplaceAll("[y]","0.5")
  //   .ReplaceAll("[z]","23.2")
  //   .ReplaceAll("[0]","1.4")
  //   .ReplaceAll("[1]","0.453645")
  //   .ReplaceAll("[2]","-0.015665");
  // TPython p;
  // float py = p.Eval(formula_forpy);
  // std::cout <<  "py: " << py <<  std::endl;
  }
  legend->AddEntry(gr[r],region[r],"l");
  mg->Add(gr[r]);
  }
  Double_t w = 600; Double_t h = 600;
  TCanvas * c1_diff_feval_vs_tformula = new TCanvas("cdiff_feval_vs_tformula", "diff_feval_vs_tformula", w, h);
  mg->Draw("AC");
  legend->Draw();
  mg->GetYaxis()->SetTitle("(TFormula-FormulaEvaluator)/TFormula");
  mg->GetYaxis()->SetRangeUser(-9e-4,9e-4);
  //  mg->GetYaxis()->SetRangeUser(-0.5,0.5);
  mg->GetXaxis()->SetTitle("p_{T}, GeV");
  c1_diff_feval_vs_tformula->SetLogx(); 
  //c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Summer16_07Aug2017_V11_AK8PF.pdf"); 
  //c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Fall17_17Nov2017_V20.pdf"); 
  //  c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Summer16_07Aug2017GH_V11_L2L3Res.pdf"); 
  c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Summer16_07Aug2017BCD_V17_L2L3Res.pdf"); 
  //  c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Fall17_17Nov2017F_V8_DATA_L2L3Res.pdf"); 
  }
