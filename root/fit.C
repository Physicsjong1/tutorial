void fit(){

  TH1F * sig_h = new TH1F("sig_h","Signal Histo",100,70,120);
  TRandom3 rndgen;
  for(int i = 0 ; i < 4000 ; i++){
    sig_h->Fill(rndgen.Gaus(91.2,2.4));
  }

  TF1 * mygaus = new TF1("mygaus", "[0]/(sqrt(2.0*3.14151927)*[2])*exp(-(x-[1])*(x-[1])/(2.0*[2]*[2]))", 70.0, 110.0);
  mygaus->SetParName(0, "Number of signal");
  mygaus->SetParName(1, "Mean");
  mygaus->SetParName(2, "Width");
  double initval1[3] = { 5000.0, 91.2, 2.4};
  mygaus->SetParameters(initval1);

  TCanvas *MyC=new TCanvas("MyC","invariant mass",1);
  sig_h->Draw();
  sig_h->Fit(mygaus, "R");
  gStyle->SetOptFit(0001);
  sig_h->SetStats(0);

  TFitResultPtr r = sig_h->Fit(mygaus, "S"); 
  r->Print();

  //r->Print("V");

  TF1 *myfunc = sig_h->GetFunction("mygaus");
  Double_t chi2 = myfunc->GetChisquare();
  Double_t p1 = myfunc->GetParameter(0);
  Double_t e1 = myfunc->GetParError(0);
  cout << "chi2 = " << chi2 << endl;
  cout << "p1 = " << p1 << endl;
  cout << "e1 = " << e1 << endl;

}
