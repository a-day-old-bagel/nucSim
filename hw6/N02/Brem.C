 void Brem() {
    struct evt_t {
    Int_t event;
    Float_t KE, pos[3],mom[3];
  };
  ifstream in;
  in.open("Brem.txt");
  evt_t evt;
  Int_t nlines=0;
  TFile *f = new TFile("Brem.root","RECREATE");
  TTree *tree = new TTree("Brem","Brem data from ascii file");
  tree->Branch("evt",&evt.event,"event/I:ke/F:posx:posy:posz:px:py:pz");
  while(in.good()){
    evt.event=nlines;
    in >> evt.KE >> evt.pos[0] >> evt.pos[1] >> evt.pos[2]   >> evt.mom[0] 
 >> evt.mom[1] >> evt.mom[2];
    /*
 *       printf( " %d  %f %f %f %f %f %f %f\n", evt.event, evt.KE, evt.pos[0], 
 *        evt.pos[1], evt.pos[2],  evt.mom[0], evt.mom[1], evt.mom[2] );
 *            */
    nlines++;
    tree->Fill();
  }
  tree->Print();
  tree->Write();  
  in.close();
  delete tree;
  delete f;
 }
