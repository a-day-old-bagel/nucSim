void DiffEXsect2root() {
    struct evt_t {
    Int_t Egamma;
    Float_t Eelectron, dSigma_dE;
  };
  ifstream in;
  in.open("DiffEXsect.dat");
  evt_t evt;
  Int_t nlines=0;
  TFile *f = new TFile("DiffEXsect.root","RECREATE");
  TTree *tree = new TTree("DiffEXsect","Compton Diff Xsect dSigma/dE");
  tree->Branch("evt",&evt.Egamma,"event/I:Eelectron/F:dSigma_dE");
  while(in.good()){
    evt.Egamma=80000;
    in >> evt.Eelectron >> evt.dSigma_dE;
    /*
     printf( " %d  %f %f %f %f %f %f %f\n",evt.event, evt.KE, evt.pos[0], evt.pos[1], evt.pos[2], evt.mom[0], evt.mom[1], evt.mom[2] );
   */
    nlines++;
    tree->Fill();
  }
 tree->Print();
 tree->Write();
 
 in.close();
 delete tree;
 delete f;
}