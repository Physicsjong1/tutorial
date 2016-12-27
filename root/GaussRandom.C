void GaussRandom(){
  TH1F * h= new TH1F("h","Histo from a Gaussian",100,-3,3);
  h->FillRandom("gaus",10000);
  h->Draw();
  TH1F * h2= new TH1F("h2","from existing histo",100,-3,3);
  h2->SetLineColor(2);
  h2->FillRandom(h, 1000);
  h2->Draw("same");
}


