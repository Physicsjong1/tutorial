void graph(){

  Int_t n = 20;
  Double_t x[n], y[n];
  for (Int_t i=0; i<n; i++) {
    x[i] = i*0.1;
    y[i] = 10*sin(x[i]+0.2);
  }
  TGraph *gr1 = new TGraph (n, x, y);

  TCanvas *c1 = new   TCanvas("c1","Graph Draw Options", 200,10,600,400);
  //Continuous Line, Axis and Stars 
  gr1->Draw("AC*"); 

  
  //(Step1) Graph Draw with Bars
  //gr1->SetFillColor(40); 
  //gr1->Draw("AB"); 

  //(Step2) Filled Bars
  //gr1->SetFillColor(45); 
  //gr1->Draw("AF"); 

   //(Step3) Marker
   //gr1->SetMarkerStyle(21);
   //gr1->Draw("APL");
   //for (Int_t j=2; j<n-1; j++) {
   //  TMarker *m = new TMarker(x[j], 0.5*y[j], 22);
   //  m->SetMarkerSize(2);
   //  m->SetMarkerColor(31+j);
   //  m->Draw();
   //}



}
