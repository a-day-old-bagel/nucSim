void asci2nt(Char_t *filename)
{
  //   create an Ntuple from a text files with 2 columns of numberse delimited by tabs
  
  ifstream in;
  in.open(filename);
  
  Float_t rnd1,rnd2;
  Int_t nlines = 0;
  TFile *f = new TFile("rns.root","RECREATE");
  TNtuple *ntuple = new TNtuple("rns","rns","rnd1:rnd2");
  
  while (1) {

    in >> rnd1 >> rnd2;
    if (!in.good()) break;

    ntuple->Fill(rnd1,rnd2);
    nlines++;
  }
  //  printf(" found %d pointsn",nlines);
  
  in.close();
  
  f->Write();
  f->Close();
  printf("read %g\t%g\n",rnd1,rnd2);
  printf("Finished reading %d rows of random numbers\n",nlines);
}
