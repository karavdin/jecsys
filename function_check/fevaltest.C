#include "CondFormats/JetMETObjects/interface/SimpleJetCorrector.h"

void fevaltest() {
  gStyle->SetOptStat(0);                                                                      
  gStyle->SetTitleSize(0.045,"x");                                                                                                                                    
  gStyle->SetTitleSize(0.045,"y");                                                                                                                                    
  gStyle->SetTitleYOffset(0.9);  

  gSystem->Load("libFWCoreFWLite.so");
  FWLiteEnabler::enable();

  //  TString formula = "max(0.0001,1-y*([1]*(z-[0])*(1+[2]*log(x/30.)))/x)"; //Summer16_07Aug2017BCD_V11_DATA_L1FastJet_AK4PFchs, Fall17_17Nov2017_V6_MC_L1FastJet_AK4PFchs
  //  TString formula = "max(0.0001,1-y/x*([1]*(z-[0])*(1+[2]*log(x/30.))))";//Summer16_07Aug2017BCD_V11_DATA_L1FastJet_AK4PFchs_fixed
  //  TString formula = "max(0.0001,1-z*([0]+([1]*x)*(1+[2]*log(y)))/y)";//Summer16_07Aug2017BCD_V11_DATA_L1FastJet_AK8PFchs
  //TString formula = "max(0.0001,1-z*([0]+[1]*(x-20.0)+[2]*log(y/30.0)+[3]*pow(log(y/30.0),2)+[4]*(x-20.0)*log(y/30.0)+[5]*(x-20.0)*pow(log(y/30.0),2))/y)";//Fall17_17Nov2017_V20
  //TString formula = "max(0.0001,1-z/y*([0]+[1]*(x-20.0)+[2]*log(y/30.0)+[3]*pow(log(y/30.0),2)+[4]*(x-20.0)*log(y/30.0)+[5]*(x-20.0)*pow(log(y/30.0),2)))";//Fall17_17Nov2017_V20_fix
  //  TString formula = "max(0.0001,1-y*([0]+[1]*(z-1.519)+[2]*pow(z-1.519,2))/x)";//L1RC
  TString formula = "max(0.0001,1-(y/x)*([0]+[1]*(z-1.519)+[2]*pow(z-1.519,2)))";//L1RC fix

  // 




  TString region[3] ={"barrel","endcap","forward"};
  TMultiGraph *mg = new TMultiGraph();
  TGraph *gr[3];
  TLegend *legend=new TLegend(0.25,0.65,0.88,0.87);
  //  TLegend *legend=new TLegend(0.15,0.65,0.89,0.87);
  legend->SetTextFont(72);
  legend->SetTextSize(0.045);
  legend->SetFillColor(0);
  //  legend->SetHeader("Summer16_07Aug2017BCD_V11_DATA_L1FastJet_AK4PFchs");
  //  legend->SetHeader("Summer16_07Aug2017_V17");
  //legend->SetHeader("Summer16_07Aug2017_V11_AK8CHS");
  //  legend->SetHeader("Summer16_07Aug2017_V11_fix");
  //legend->SetHeader("Fall17_17Nov2017_V20");
  legend->SetHeader("Fall17_17Nov2017_V20_fix");


  for(int r=0;r<3;r++){
    //std::cout<<region[r]<<std::endl;
    gr[r] = new TGraph(); 
    gr[r]->SetLineColor(r+1);  gr[r]->SetMarkerColor(r+1); gr[r]->SetLineWidth(4-r);
    //    double par[3];
    double par[6];
    par[0] = 1.4;
    if(r==0){
      // par[0] = 5.624363065;  par[1]=0.4276560226; par[2]=-2.060861763;
      // par[3] = -0.4477129734; par[4]=-0.0404846605; par[5]=0.002292540287;
      par[0]=-0.648831;par[1]=0.404567;par[2]=0.0432184;
      //      par[1] = 0.370561; par[2] = -0.005034; 
      //      par[1] = 0.432954; par[2]=-0.005034;
      //      par[1] = 0.522508; par[2] = -0.069581;//barrel
    }
    if(r==1){
      // par[0] = 3.324906377; par[1]=0.2551097957; par[2]=-2.595802971;
      // par[3] = 0.2068205717; par[4]=-0.07551787685; par[5]=0.04997147999;
      par[0]=0.346563;par[1]=0.107782;par[2]=0.562244;
      //      par[1] = 0.307064; par[2] = 0.042583;
      //      par[1] = 0.394049; par[2]=0.042583;
      //      par[1] = 0.594004; par[2] = -0.027694;//EC
    }
    if(r==2){
      // par[0] = 13.32876529; par[1]=0.7134224199; par[2]=-1.166806527; 
      // par[3]=-1.381177982;par[4]=-0.06575356223; par[5]=-0.07371937846;
      par[0]=-0.826258;par[1]=0.199119;par[2]=0.620713;                 
      //      par[1] = 0.648374; par[2]=-0.001601;
      //    par[1]=0.737128; par[2]=-0.001601;
      //      par[1] = 0.707857; par[2] = 0.057185;//HF
    }

    double pt[17]={15,17,20,30,40,50,60,70,80,90,100,200,400,600,800,1000,2000};
  for(int i=0;i<17;i++){
    //    std::cout<<"pt = "<<pt[i]<<std::endl;
    //double x[4] = { pt[i], 0.4*TMath::Pi(), 23.2 };//AK4CHS, Summer16_07Aug2017BCD_V11
    //    double x[4] = { pt[i], 0.4*TMath::Pi(), 32.1 };//AK4CHS, Fall17_17Nov2017_V6
    //    double x[4] = { pt[i], 0.8*TMath::Pi(), 32.1 };//AK8CHS, Fall17_17Nov2017_V6
    //    double x[4] = {23.2, pt[i],0.4*TMath::Pi()};//AK8CHS, Summer16_07Aug2017BCD_V11
    double x[4] = {32.1, pt[i],0.4*TMath::Pi()};//AK4CHS, Fall17_17Nov2017_V20

    //    double par[3] = { 1.4, 0.453645, -0.015665 };

  reco::FormulaEvaluator mFunc(formula.Data());
  float fe = mFunc.evaluate(reco::formula::ArrayAdaptor(x,3), reco::formula::ArrayAdaptor(par,3) );
  //  float fe = mFunc.evaluate(reco::formula::ArrayAdaptor(x,3), reco::formula::ArrayAdaptor(par,6) );
  std::cout <<  "fe: " << fe <<  std::endl;

  TFormula f1("f1",formula);
  f1.SetParameter(0, par[0]);
  f1.SetParameter(1, par[1]);
  f1.SetParameter(2, par[2]);
  // f1.SetParameter(3, par[3]);
  // f1.SetParameter(4, par[4]);
  // f1.SetParameter(5, par[5]);

  float tf = f1.Eval(x[0],x[1],x[2]);
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
  //  mg->GetYaxis()->SetRangeUser(-0.1,0.5);
  mg->GetXaxis()->SetTitle("p_{T}, GeV");
  c1_diff_feval_vs_tformula->SetLogx(); 
  //c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Summer16_07Aug2017_V11_AK8PF.pdf"); 
  //c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Fall17_17Nov2017_V20.pdf"); 
  c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Fall17_17Nov2017_V20_fix.pdf"); 
  //  c1_diff_feval_vs_tformula->SaveAs("Diff_feval_vs_tformula_Summer16_07Aug2017_V17_L2L3Res.pdf"); 
  }
