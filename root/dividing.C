void dividing(){

  TH1F * gaus_1 = new TH1F("gaus_1","Gauss Histo1",30,0,10);
  TH1F * gaus_2 = new TH1F("gaus_2","Gauss Histo2",30,0,10);
  TRandom3 rndgen;
  gaus_1->Sumw2();
  gaus_2->Sumw2();
  for(int i = 0 ; i < 4000 ; i++){
    if( i%4 == 0 ) gaus_1->Fill(rndgen.Gaus(5,2));
    if( i%4 == 0 ) gaus_2->Fill(rndgen.Gaus(5,2));
  }
  TH1F * divide_h =  new TH1F(*gaus_1);
  divide_h->Divide(gaus_2);
  divide_h->SetTitle(" ; Xaxis ; Yaxis");

  TCanvas * c = new TCanvas("c","c",1);
  c->Divide(1,2);
  c->cd(1);
  gaus_1->Draw();
  gaus_2->Draw();
  c->cd(2);
  divide_h->Draw();
  c->cd();
  
}
