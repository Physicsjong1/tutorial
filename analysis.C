void analysis(const char *inputFile1, const char *inputFile2){

  TFile * f_sig = new TFile(inputFile1);
  TFile * f_bkg = new TFile(inputFile2);
  TH1F * h_nbjet_sig = (TH1F*) f_sig->Get("nbjet");
  TH1F * h_mbb_sig = (TH1F*) f_sig->Get("mbb");
  TH1F * h_nbjet_bkg = (TH1F*) f_bkg->Get("nbjet");
  TH1F * h_mbb_bkg = (TH1F*) f_bkg->Get("mbb");

  TCanvas * c_nbjet = new TCanvas("c_nbjet","c_nbjet",1);
  h_nbjet_sig->Draw();
  h_nbjet_bkg->Draw("same");
  h_nbjet_sig->SetLineColor(2);
  h_nbjet_bkg->SetLineColor(4);
  h_nbjet_sig->SetMaximum(5000);
  h_nbjet_sig->SetStats(0);
  h_nbjet_sig->GetXaxis()->SetTitle("Number of b jets");
  h_nbjet_sig->GetYaxis()->SetTitle("Number of Events");

  TLegend * l = new TLegend(0.65,0.65,0.85,0.85);
  l->AddEntry(h_nbjet_sig,"signal","L");
  l->AddEntry(h_nbjet_bkg,"background","L");
  l->SetTextSize(0.05);
  l->SetLineColor(0);
  l->SetFillColor(0);
  l->Draw();

}
