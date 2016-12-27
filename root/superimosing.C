void superimposing(){
  
  gr1->SetLineColor(4);
  gr1->Draw("AC*");
  // superimpose the second graph by leaving out   the axis option "A"
  gr2->SetLineWidth(3);
  gr2->SetMarkerStyle(21);
  gr2->SetLineColor(2);
  gr2->Draw("CP");
}



