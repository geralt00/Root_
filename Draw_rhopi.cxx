#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include <string>
#include <string.h>
#include "TString.h"
#include "TLorentzVector.h"
#include <iostream>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "TH1F.h"
#include "TH2F.h"


void Draw_rhopi(){
        gROOT->Reset();
        gROOT->SetStyle("Pub");
        gStyle->SetPalette(1);
        gStyle->SetCanvasBorderMode(0);
        gStyle->SetCanvasBorderSize(0);
        gStyle->SetCanvasColor(10);
        gStyle->SetLabelFont(42,"xyz");
        gStyle->SetLabelSize(0.06,"xyz");
        gStyle->SetLabelOffset(0.01,"xyz");
        gStyle->SetNdivisions(510,"xyz");
        gStyle->SetTitleFont(42,"xyz");
        gStyle->SetTitleColor(1,"xyz");
        gStyle->SetTitleSize(0.07,"xyz");

        gStyle->SetTitleOffset(1.,"xyz");
        gStyle->SetPadBorderMode(0);
        gStyle->SetPadBorderSize(0);
        gStyle->SetPadColor(10);
        gStyle->SetPadLeftMargin(0.17);
        gStyle->SetPadBottomMargin(0.2);
        gStyle->SetPadRightMargin(0.05);
        gStyle->SetPadTopMargin(0.05);
        gStyle->SetLegendBorderSize(0);
        gStyle->SetOptDate(0);
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(0);
        gStyle->SetOptTitle(0);
        gStyle->SetOptTitle(kFALSE);

        gStyle->SetLineWidth(3);
        gStyle->SetMarkerSize(1);
        gStyle->SetMarkerStyle(20);
        gStyle->SetMarkerColor(1);
        gStyle->SetLineColor(1);

 
 
  
  TH1F *hmrhp  =new TH1F("m_mrhp",  "mrhp", 100, 0,3.0);
  TH1F *hmrhm  =new TH1F("m_mrhm",  "mrhm", 100, 0,3.0);
  TH1F *hmrh0  =new TH1F("m_mrh0",  "mrh0", 100, 0,3.0);
  TH1F *hmpi0  =new TH1F("m_mpi0",  "mpi0", 100, 0,0.2);

  TH1F *hmrhm_mc  =new TH1F("mrhp_mc",   "mrhp_mc", 100, 0,3.0);
  TH1F *hmrhp_mc  =new TH1F("mrhm_mc",   "mrhm_mc", 100, 0,3.0);
  TH1F *hmrh0_mc  =new TH1F("m_mrh0_mc", "mrh0_mc", 100, 0,3.0);
  TH1F *hmpi0_mc  =new TH1F("m_mpi0_mc", "mpi0_mc", 100, 0,0.2);

  TH1F *hsideband1  =new TH1F("hsideband1",  "sideband1", 100, 0, 3.0);

// ---------- data -----------------------------  
cout<<""**********data************"<<endl
   if(1){

   TFile * file = new TFile("your root file with truth data");
   TTree * t_data = (TTree *)file->Get("vxyzmix");

  Double_t mrhp;
  Double_t mrhm;
  Double_t mrh0;
  Double_t mpi0;

  t_data->SetBranchAddress("mrhp",    &mrhp);
  t_data->SetBranchAddress("mrhm",    &mrhm);
  t_data->SetBranchAddress("mpi0",    &mpi0);
  t_data->SetBranchAddress("mrh0",    &mrh0);
  
int ncount=0, N4C1 =0, N4C3=0, Ndec =0;
   int Nsideband =0;

   for(int i=0; i<t_data->GetEntries(); i++)
    {
     t_data->GetEntry(i);

          {
 if(fabs(mrh0 - 0.135) <= 0.015 )
  hsideband1->Fill(mrh0);
 if(fabs(mrh0-0.135)<=0.070&&fabs(mrh0 - 0.135) >= 0.055 )
  hsideband1->Fill(mrh0, 1.0);
  hmrhp->Fill(mrhp);
  hmrh0->Fill(mrh0);
  hmrhm->Fill(mrhm);
  hmpi0->Fill(mpi0);
     }
     }  // a end  
  }

cout<<"  ------ MC -------         "<<endl;
// ---------- MC -----------------------------  

   if(2){

   TFile * file = new TFile("your root file with monte carlo");
   TTree * t_mc = (TTree *)file->Get("vxyzmix");

  Double_t mrhp;
  Double_t mrhm;
  Double_t mrh0;
  Double_t mpi0;

  t_mc->SetBranchAddress("mrhp",      &mrhp);
  t_mc->SetBranchAddress("mrhm",      &mrhm);
  t_mc->SetBranchAddress("mpi0",      &mpi0);
  t_mc->SetBranchAddress("mrh0",      &mrh0);

  
   int ncount=0, N4C1_mc =0, N4C3_mc=0, Ndec_mc =0;
   int Nmc1=0, Nmc2=0, Nmc3=0;
   
   for(int i=0; i<t_mc->GetEntries(); i++)
    {
     t_mc->GetEntry(i);
          {    
hmrhp_mc->Fill(mrhp);
hmrhm_mc->Fill(mrhm);
hmrh0_mc->Fill(mrh0);
hmpi0_mc->Fill(mpi0);         
 }   
     }

 }
//---------------------------------------------------------------------------
//*************************Draw part***************************************//

   TCanvas *c1 = new TCanvas("total_MC & exeperiment", "c1", 0, 0, 1500,800);
   c1->Divide(2,2);
   c1->cd(1) ; gPad->SetLeftMargin(0.2) ;
   hmrhm->GetYaxis()->SetTitle("Events");
   hmrhm->GetXaxis()->SetTitle("Mass(#rho-) Gev/c^2");
   hmrhm->GetXaxis()->CenterTitle();
   hmrhm->GetYaxis()->CenterTitle();
   hmrhm->SetLineColor(1);
   hmrhm->Draw("ep");//point
   hmrhm->SetNdivisions(505, "x");
//   hmrhp0->SetRangeUser(0,1600);
//   hmrhp0_mc->Scale(hmrhp0->GetEntries()/hmrhp0_mc->GetEntries());
   hmrhm_mc->Scale(hmrhm->GetMaximum()/hmrhm_mc->GetMaximum());
   hmrhm_mc->SetLineColor(4);
   hmrhm_mc->Draw("same");



   leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(hmrhm,    "Data",        "PL");
   leg->AddEntry(hmrhm_mc,  "MC",    "l"); 
   leg->SetFillColor(10);
   leg->Draw();    
 

/*
   TCanvas *c2 = new TCanvas("c2", "c2", 0, 0, 800,600);*/
   c1->cd(2) ; gPad->SetLeftMargin(0.2);
   hmrhp->GetYaxis()->SetTitle("Events");
   hmrhp->GetXaxis()->SetTitle("Mass(#rho+) Gev/c^2");
   hmrhp->GetXaxis()->CenterTitle();
   hmrhp->GetYaxis()->CenterTitle();
   hmrhp->SetLineColor(1);
   hmrhp->Draw("ep");
                             
//   hmrhp_mc->Scale(hmrhp->GetEntries()/hmrhp_mc->GetEntries());
   hmrhp_mc->Scale(hmrhp->GetMaximum()/hmrhp_mc->GetMaximum());
   hmrhp_mc->SetLineColor(4);
   hmrhp_mc->Draw("same");

   leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(hmrhp,    "Data",        "PL");
   leg->AddEntry(hmrhp_mc,  "MC",    "l"); 
   leg->SetFillColor(10);
   leg->Draw();


   c1->cd(3) ; gPad->SetLeftMargin(0.2);
   hmrh0->GetYaxis()->SetTitle("Events");
   hmrh0->GetXaxis()->SetTitle("Mass(#rho0) Gev/c^2");
   hmrh0->GetXaxis()->CenterTitle();
   hmrh0->GetYaxis()->CenterTitle();
   hmrh0->SetLineColor(1);
   hmrh0->Draw("ep");
   hmrh0_mc->Scale(hmrh0->GetMaximum()/hmrh0_mc->GetMaximum());
   hmrh0_mc->SetLineColor(4);
   hmrh0_mc->Draw("same");


   leg = new TLegend(0.7,0.7,0.9,0.9);
   leg->AddEntry(hmrh0,    "Data",        "PL");
   leg->AddEntry(hmrh0_mc,  "MC",    "l");
   leg->AddEntry(hsideband1,  "sideband",    "l");
   leg->SetFillColor(10);
   leg->Draw();
   hsideband1->SetLineColor(3);
   hsideband1->Draw("same");
/*
   TArrow *arrow1 = new TArrow(0.07, 1000,    0.07,  20,  0.04);
   arrow1->SetLineColor(4);
   arrow1->SetLineWidth(1);
   arrow1->Draw();

   TArrow *arrow2 = new TArrow(0.085, 1000,    0.085,  20,  0.04);
   arrow2->SetLineColor(4);
   arrow2->SetLineWidth(1);
   arrow2->Draw();

   TArrow *arrow3 = new TArrow(0.12, 1000,    0.12,  10,  0.04);
   arrow3->SetLineColor(3);
   arrow3->SetLineWidth(1);
   arrow3->Draw();

   TArrow *arrow4 = new TArrow(0.14, 1000,    0.14,  10,  0.04);
   arrow4->SetLineColor(3);
   arrow4->SetLineWidth(1);
   arrow4->Draw();

   TArrow *arrow5 = new TArrow(0.19, 1000,    0.19,  10,  0.04);
   arrow5->SetLineColor(3);
   arrow5->SetLineWidth(1);
   arrow5->Draw();

   TArrow *arrow6 = new TArrow(0.205, 900,    0.205,  10,  0.04);
   arrow6->SetLineColor(3);
   arrow6->SetLineWidth(1);
   arrow6->Draw();
*/

   c1->cd(4) ; gPad->SetLeftMargin(0.2);
   hmpi0->GetYaxis()->SetTitle("Events");
   hmpi0->GetXaxis()->SetTitle("Mass(#pi0) Gev/c^2");
   hmpi0->GetXaxis()->CenterTitle();
   hmpi0->GetYaxis()->CenterTitle();
   hmpi0->SetLineColor(1);
   hmpi0->Draw("ep");
   hmpi0_mc->Scale(hmpi0->GetMaximum()/hmpi0_mc->GetMaximum());
   hmpi0_mc->SetLineColor(4);
   hmpi0_mc->Draw("same");

   leg = new TLegend(0.3,0.3,0.5,0.5);
   leg->AddEntry(hmrh0,    "Data",        "PL");
   leg->AddEntry(hmrh0_mc,  "MC",    "l");
   leg->SetFillColor(10);//white
   leg->Draw();
/*
   TArrow *arrow1 = new TArrow(0.573, 1000,    0.573,  20,  0.04);
   arrow1->SetLineColor(4);
   arrow1->SetLineWidth(3);
   arrow1->Draw();

   TArrow *arrow2 = new TArrow(0.523, 1000,    0.523,  20,  0.04);
   arrow2->SetLineColor(4);
   arrow2->SetLineWidth(3);
   arrow2->Draw();

   TArrow *arrow3 = new TArrow(0.608, 900,    0.608,  10,  0.04);
   arrow3->SetLineColor(3);
   arrow3->SetLineWidth(3);
   arrow3->Draw();

   TArrow *arrow4 = new TArrow(0.488, 900,    0.488,  10,  0.04);
   arrow4->SetLineColor(3);
   arrow4->SetLineWidth(3);
   arrow4->Draw();

   TArrow *arrow5 = new TArrow(0.513, 900,    0.513,  10,  0.04);
   arrow5->SetLineColor(3);
   arrow5->SetLineWidth(3);
   arrow5->Draw();

   TArrow *arrow6 = new TArrow(0.583, 900,    0.583,  10,  0.04);
   arrow6->SetLineColor(3);
   arrow6->SetLineWidth(3);
   arrow6->Draw();

//  c2->Print("Mchiqure.eps");


*/  



}

