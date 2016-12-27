void SigAndBack(){

  TH1F * sig_h = new TH1F("sig_h","Signal Histo",50,0,10);
  TH1F * bkg_h = new TH1F("bkg_h","Exponetial Histo",50,0,10);
  sig_h->Sumw2();
  bkg_h->Sumw2();
  TRandom3 rndgen;
  for(int i = 0 ; i < 4000 ; i++){
    bkg_h->Fill(rndgen.Exp(4));
    if( i%10 == 0 ) sig_h->Fill(rndgen.Gaus(5,0.5));
  }
  TH1F * sum_h =  new TH1F(*bkg_h);
  sum_h->Add(sig_h, 1.0);

  sum_h->Draw("H");
  sig_h->Draw("Hsame");
  bkg_h->Draw("Hsame");
  
  sum_h->SetLineWidth(4);
  sig_h->SetLineWidth(4);
  bkg_h->SetLineWidth(4);

  sum_h->SetLineColor(4); 
  sig_h->SetLineColor(1);
  bkg_h->SetLineColor(2);
  
}
