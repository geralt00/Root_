#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include <string>
#include <string.h>
#include "TString.h"
#include "TLorentzVector.h"
#include <iostream>
#include <iostream>
#include "TCut.h"
#include <string>
#include <sstream>
#include <fstream>
#include <math.h>
#include "TH1F.h"
#include "TH2F.h"

void momentum()
{
   gROOT->Reset();
   gROOT->SetStyle("Pub");
   gStyle->SetPalette(1);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetCanvasColor(10);

   gStyle->SetLabelFont(42, "xyz");
   gStyle->SetLabelSize(0.04, "xyz");
   gStyle->SetLabelOffset(0.01, "xyz");
   gStyle->SetLabelColor(1, "xyz");
   gStyle->SetNdivisions(510, "xyz");

   gStyle->SetTitleFont(42, "xyz");
   gStyle->SetTitleColor(1, "xyz");
   gStyle->SetTitleSize(0.05, "xyz");
   gStyle->SetTitleOffset(1.5, "xyz"); // distance between title and graph

   gStyle->SetPadBorderMode(0);
   gStyle->SetPadBorderSize(0.05);
   gStyle->SetPadColor(4);
   gStyle->SetPadLeftMargin(0.17);
   gStyle->SetPadBottomMargin(0.2);
   gStyle->SetPadRightMargin(0.05);
   gStyle->SetPadTopMargin(0.05);
   gStyle->SetLegendBorderSize(0.5);
   gStyle->SetOptDate(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(0);
   gStyle->SetOptTitle(0);
   gStyle->SetOptTitle(kFALSE);

   gStyle->SetLineWidth(3);
   gStyle->SetMarkerSize(0.05);
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerColor(1);
   gStyle->SetLineColor(4); // label outer line

   TH1F *P = new TH1F("P", "P", 50, -1, 1);
   TH1F *Px = new TH1F("Px", "Px", 50, -1, 1);
   TH1F *Py = new TH1F("Py", "Py", 50, -1, 1);
   TH1F *Pz = new TH1F("Pz", "Pz", 50, -1, 1);
   TH1F *P_mc = new TH1F("P_mc", "P_mc", 50, -1, 1);
   TH1F *Px_mc = new TH1F("Px_mc", "Px_mc", 50, -1, 1);
   TH1F *Py_mc = new TH1F("Py_mc", "Py_mc", 50, -1, 1);
   TH1F *Pz_mc = new TH1F("Pz_mc", "Pz_mc", 50, -1, 1);

   // ---------- data -----------------------------

   if (1)
   {
      TFile *file = new TFile("46802.root");

      TTree *t_data = (TTree *)file->Get("lkpi0");
      Double_t p, px, py, pz;
      t_data->SetBranchAddress("P", &p);
      t_data->SetBranchAddress("Px", &px);
      t_data->SetBranchAddress("Py", &py);
      t_data->SetBranchAddress("Pz", &pz);

      for (int i = 0; i < t_data->GetEntries(); i++)
      {
         t_data->GetEntry(i);
         {
            P->Fill(p);
            Px->Fill(px);
            Py->Fill(py);
            Pz->Fill(pz);
         }
      }
   }

   cout << "  ------ MC -------         " << endl;

   if (2)
   {

      TFile *file = new TFile("pi0.root");

      TTree *t_mc = (TTree *)file->Get("lkpi0");
      Double_t p, px, py, pz;
      t_mc->SetBranchAddress("P", &p);
      t_mc->SetBranchAddress("Px", &px);
      t_mc->SetBranchAddress("Py", &py);
      t_mc->SetBranchAddress("Pz", &pz);
      for (int i = 0; i < t_mc->GetEntries(); i++)
      {
         t_mc->GetEntry(i);
         {
            P_mc->Fill(p);
            Px_mc->Fill(px);
            Py_mc->Fill(py);
            Pz_mc->Fill(pz);
         }
      }
   }

   //---------------------------------------------------------------------------
   //*************************Draw part***************************************//

   TPaveText *pt = new TPaveText(0.8, 0.9, 0.95, 0.95, "brNDC");
   pt->SetFillColor(4);
   pt->SetTextAlign(12);
   pt->AddText("#Lambda^{+}_{c}#rightarrow#LambdaK^{+}#pi^{0}");
   pt->SetTextColor(kWhite);

   leg = new TLegend(0.5, 0.5, 0.2, 0.7);
   leg->AddEntry(P, "data", "EL");
   leg->AddEntry(P_mc, "signalMC", "L");
   leg->SetFillColor(10); // white

   TCanvas *c1 = new TCanvas("1", "c1", 0, 0, 800, 600);
   // c1->Divide(2);
   c1->cd(1);
   gPad->SetLeftMargin(0.2); //?

   P->GetYaxis()->SetTitle("Events");
   P->GetXaxis()->SetTitle("P (Gev/c)");
   P->GetYaxis()->CenterTitle();
   P->SetLineColor(1);
   P->Draw("el"); // point
   P->SetNdivisions(505, "x");
   P->SetNdivisions(505, "y");
   P_mc->Scale(P->GetEntries() / P_mc->GetEntries());
   P_mc->GetYaxis()->SetTitle("Events");
   P_mc->GetYaxis()->CenterTitle(); // default right side
   P_mc->SetLineColor(kRed);
   P_mc->SetNdivisions(505, "x");
   P_mc->SetNdivisions(505, "y");
   P_mc->Draw("same"); // histogram
   leg->Draw();
   pt->Draw();
   TCanvas *c2 = new TCanvas("2", "c2", 0, 0, 800, 600);
   c2->cd(1);
   gPad->SetLeftMargin(0.2);
   Px->GetYaxis()->SetTitle("Events");
   Px->GetXaxis()->SetTitle("Px (Gev/c)");
   Px->GetYaxis()->CenterTitle();
   Px->SetLineColor(1);
   Px->Draw("el"); // point
   Px->SetNdivisions(505, "x");
   Px->SetNdivisions(505, "y");
   Px_mc->Scale(P->GetEntries() / P_mc->GetEntries());
   Px_mc->GetYaxis()->SetTitle("Events");
   Px_mc->GetYaxis()->CenterTitle(); // default right side
   Px_mc->SetLineColor(kRed);
   Px_mc->SetNdivisions(505, "x");
   Px_mc->SetNdivisions(505, "y");
   Px_mc->Draw("same"); // histogram
   leg->Draw();
   pt->Draw();
   TCanvas *c3 = new TCanvas("3", "c2", 0, 0, 800, 600);
   c3->cd(1);
   gPad->SetLeftMargin(0.2);
   Py->GetYaxis()->SetTitle("Events");
   Py->GetXaxis()->SetTitle("Py (Gev/c)");
   Py->GetYaxis()->CenterTitle();
   Py->SetLineColor(1);
   Py->Draw("el"); // point
   Py->SetNdivisions(505, "x");
   Py->SetNdivisions(505, "y");
   Py_mc->Scale(P->GetEntries() / P_mc->GetEntries());
   Py_mc->GetYaxis()->SetTitle("Events");
   Py_mc->GetYaxis()->CenterTitle(); // default right side
   Py_mc->SetLineColor(kRed);
   Py_mc->SetNdivisions(505, "x");
   Py_mc->SetNdivisions(505, "y");
   Py_mc->Draw("same"); // histogram
   leg->Draw();
   pt->Draw();
   TCanvas *c4 = new TCanvas("4", "c2", 0, 0, 800, 600);
   c4->cd(1);
   gPad->SetLeftMargin(0.2);
   Pz->GetYaxis()->SetTitle("Events");
   Pz->GetXaxis()->SetTitle("Pz (Gev/c)");
   Pz->GetYaxis()->CenterTitle();
   Pz->SetLineColor(1);
   Pz->Draw("el"); // point
   Pz->SetNdivisions(505, "x");
   Pz->SetNdivisions(505, "y");
   Pz_mc->Scale(P->GetEntries() / P_mc->GetEntries());
   Pz_mc->GetYaxis()->SetTitle("Events");
   Pz_mc->GetYaxis()->CenterTitle(); // default right side
   Pz_mc->SetLineColor(kRed);
   Pz_mc->SetNdivisions(505, "x");
   Pz_mc->SetNdivisions(505, "y");
   Pz_mc->Draw("same"); // histogram
   leg->Draw();
   pt->Draw();
}
