#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>

// I hate typing out "unsigned"
typedef unsigned int uint; 


// FUNCTION PROTOTYPES
int tqkf();
int spxj();
bool uemufi(double owsyz, double sssb);
void snailw(int* ppfw, int xkgr);
bool wxwi(int xlo_s[4], char* orcv, int lggvlu, const char* rrphbr);
bool tt_s(int znokdz, char** hmxitd, char*& nadaky, int& dkfih);
unsigned int slkadj(unsigned int t_dp);
int vqqd();
float bwipyp(int shjbpx, int sssb, int ayjt, int nrkhfm, int g_vutr);
int vtntid(int ufbnjw, int ii_n);
bool rrlwrj(const std::vector<int> oxgc, const std::vector<int> gqszp);
int blq__();
int rvpb(std::vector<int>& hf__f);




int spxj() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int znsjn = 25;
  int** xlo_s = new int*[znsjn];
  for(int oomqy=0; oomqy<znsjn; ++oomqy) { 
    xlo_s[oomqy] = new int[znsjn];
    for(int adne=0; adne<znsjn; ++adne) {
      xlo_s[oomqy][adne] = 0;
    }
  }

  

  // sanity check: corners of array
  assert(xlo_s[0][0] == 0);
  assert(xlo_s[znsjn-1][0] == 0);
  assert(xlo_s[0][znsjn-1] == 0);
  assert(xlo_s[znsjn-1][znsjn-1] == 0);

  // store pythagorean numbers in xlo_s
  for(int oomqy=0; oomqy<znsjn; ++oomqy) {   
    for(int adne=0; adne<znsjn; ++adne) { 
      xlo_s[oomqy][adne] = vtntid(oomqy, adne);
    }
  }
  // do some checks
  assert(xlo_s[1][2] == -1); // no triple exists
  assert(xlo_s[3][4] == 5);
  assert(xlo_s[5][4] == 3);
  assert(xlo_s[13][12] == 5);
  assert(xlo_s[8][15] == 17);
  assert(xlo_s[8][16] != 17);
  assert(xlo_s[17][8] == 15);
  assert(xlo_s[5][3] == xlo_s[3][5]);
  assert(xlo_s[7][24] == 25);
  assert(xlo_s[12][16] == 20); // 3-4-5 triple times 4
  assert(xlo_s[5][15] == -1);
  assert(xlo_s[24][7] != -1);

  /* Now iterate over and print xlo_s, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** zavt = xlo_s;
  int** ud_s = lunsul;
  for(int oomqy = 1; oomqy <= znsjn; ++oomqy, ++zavt) {
    int* gkezbg = *zavt;
    for(int adne = 1; adne <= znsjn; ++adne, ++gkezbg) {
      int wxgsl = *gkezbg;
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string vbvpoo = ((wxgsl < 10 && wxgsl > -1) ? " " : "");
      std::cout << vbvpoo << *gkezbg << " ";
    }
    std:: cout << std::endl;
  }


  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int wwzg = 0;
  for(int oomqy=5; oomqy<18; ++oomqy) {
    for(int adne=3; adne<10; ++adne) {
      wwzg += xlo_s[oomqy][adne];
    }
  }
  for(int oomqy=0; oomqy<znsjn; ++oomqy) {
    delete [] xlo_s[oomqy];
  }
  delete [] xlo_s;
  return wwzg;
  //********************************************************************************
}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float bwipyp(int shjbpx, int sssb, int ayjt, int nrkhfm, int g_vutr) {
  float xucb = ((((float(shjbpx) / float(sssb)) / float(ayjt)) / float(nrkhfm)) / float(g_vutr));
  return xucb;
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int slkadj(unsigned int t_dp) {
  union __sys_rcu_tdb_ {
    unsigned int hmzd;
    float vsqn;
  } rtjn;
  rtjn.hmzd = (t_dp * 27828) + 1456694363;
  rtjn.vsqn /= 1024;
  rtjn.hmzd ^= 1672983815;
  rtjn.hmzd += (t_dp * t_dp ^ (t_dp + rtjn.hmzd));
  unsigned int yjufs = (rtjn.hmzd >> 21) & 2047;
  unsigned int uuckim = (rtjn.hmzd << 11) & 037777774000;
  rtjn.vsqn -= 10;
  rtjn.hmzd ^= (yjufs | uuckim);
  return rtjn.hmzd;
}

int blq__() {

  // create a vector oxgc with 7 entries of 25
  std::vector<int> oxgc(7, 25);
  // create another vector with entries 1-10
  std::vector<int> gqszp;
  for(uint zbics=1; zbics<=10; ++zbics) {
    gqszp.push_back(zbics);
  }
  // and one with entries -5 to 5
  std::vector<int> igbm;
  for(int cmnk=-5; cmnk<=5; ++cmnk) {
    igbm.push_back(cmnk);
  }
  assert(igbm[5] == 0);

  int rnh_ = rvpb(oxgc);
  int aefu = rvpb(gqszp);
  int ozns = rvpb(igbm);
  assert(rnh_ == 175);
  assert(oxgc[2] == 75);
  assert(oxgc[5] == 150);
  assert(aefu == 55);
  assert(gqszp[2] == 6);
  assert(ozns == 0);
  assert(igbm[10] == 0);
  for(uint buxh=0; buxh<igbm.size(); ++buxh) { assert(igbm[buxh] <= 0); }
  int ysamk = rvpb(oxgc);
  int qoyafo = rvpb(gqszp);
  assert(ysamk == 700);
  assert(oxgc[2] == 150);
  for(uint hykfw=0; hykfw<oxgc.size(); ++hykfw) { assert(oxgc[hykfw] != 225); }
  assert(oxgc[5] == 525);

  int syzw = 0;
  for(uint kmlco=0; kmlco<gqszp.size(); ++kmlco) {
    // count the number of multiples of 10 in gqszp
    if(gqszp[kmlco] % 10 == 0) {
      syzw++;
    }
  }
  // there should be 4 of them
  assert(syzw == 4);


  // more vectors
  std::vector<int> j_lwo;
  j_lwo.push_back(4);
  j_lwo.push_back(23);
  j_lwo.push_back(18);
  j_lwo.push_back(31);
  j_lwo.push_back(167);
  j_lwo.push_back(213);
  j_lwo.push_back(86);
  std::vector<int> xh_j_o;
  xh_j_o.push_back(-7);
  xh_j_o.push_back(10);
  xh_j_o.push_back(806);
  xh_j_o.push_back(211);
  // create s_kk by concatenating j_lwo and xh_j_o
  std::vector<int> s_kk(j_lwo);
  for(uint hykfw=0; hykfw<xh_j_o.size(); ++hykfw) { s_kk.push_back(xh_j_o[hykfw]); }

  assert(s_kk.size() == 11);
  assert(s_kk[6] == 86);
  assert(s_kk[7] == -7);
  assert(s_kk[10] == 211);

  // compare some vectors
  assert(rrlwrj(oxgc, j_lwo));   
  assert(! rrlwrj(xh_j_o, oxgc)); 
  assert(rrlwrj(s_kk, igbm));   
  assert(! rrlwrj(igbm, s_kk)); 
  assert(! rrlwrj(gqszp, xh_j_o)); 
  assert(! rrlwrj(s_kk, oxgc)); 

  // now concatenate everything into a big vector
  std::vector<int> osxmg(oxgc);
  osxmg.insert(osxmg.end(), gqszp.begin(), gqszp.end());
  osxmg.insert(osxmg.end(), igbm.begin(), igbm.end());
  // j_lwo and xh_j_o are already concatenated into s_kk
  // so just concatenate that
  osxmg.insert(osxmg.end(), s_kk.begin(), s_kk.end());
  assert(osxmg.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> edrrn;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
  syzw = 0;
  for(uint zlvvaw = 0; zlvvaw < osxmg.size(); zlvvaw++) {
    if(osxmg[zlvvaw] % 3 == 0) {
      // std::cout << osxmg[zlvvaw] << " is divisible by 3" << std::endl;
      syzw++;
      edrrn.push_back(osxmg[zlvvaw]);
    }
  }
  std::cout << "There are " << syzw << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(int otferi=syzw-1; otferi > -1; --otferi) {
    std::cout << "edrrn[" << otferi << "] = " << edrrn[otferi] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  syzw += ysamk + qoyafo;
  syzw += (osxmg.size() == 40);
  for(uint kmlco=13;kmlco<24;++kmlco) { syzw += (int) osxmg[kmlco]; }
  syzw *= rvpb(edrrn)/2;
  return syzw;
  //********************************************************************************
}


int tqkf() {

  // set up some variables
  int ecgsg = 10;
  int wzufh = 46;
  int psmmk = 4;
  int wjfbq = psmmk - wzufh; // -42 
  int mswnqz = wzufh - 3*ecgsg + 4*psmmk; //  32 
  int ibfgwy = 2*wzufh + 2*psmmk; //  100 
  int dcehir = mswnqz - (wzufh / psmmk) + wjfbq + 20; // -1 
  int hqnjz = ceil(float(ibfgwy / psmmk) / float(ecgsg)); //  3 
  int pycb = (wjfbq / hqnjz) / 7; // -2 
  int ylyix = dcehir + pycb; // -3 
  int qfh_c = ((ibfgwy / mswnqz) - hqnjz) -1; // -1 
  int obotrc = ibfgwy + 2*wjfbq; // 16 
  int clzgz = dcehir + pycb + qfh_c + ylyix -1; // -8  
  float kmutj = float(ecgsg) / float(ibfgwy); // 0.1 

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << bwipyp(ibfgwy, dcehir, psmmk, 5, dcehir)
        << " (expected 5)." << std::endl;

  assert(bwipyp(ibfgwy,dcehir,psmmk,5,dcehir) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << bwipyp(840, wjfbq, pycb, qfh_c, 1)
        << " (expected -10)." << std::endl;

  assert(bwipyp(840, wjfbq, pycb, qfh_c, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << bwipyp(320, clzgz, qfh_c, ecgsg, pycb)
        << " (expected -2)." << std::endl;

  assert(bwipyp(320, clzgz, qfh_c, ecgsg, pycb) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << bwipyp((mswnqz*ibfgwy*-1), qfh_c, obotrc, clzgz, (ecgsg/2))
        << " (expected -5)." << std::endl;

  assert(bwipyp(mswnqz*ibfgwy*-1, qfh_c, obotrc, clzgz, (ecgsg/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float clxk = bwipyp(ibfgwy*10, ecgsg, ecgsg, ecgsg, ecgsg);
  std::cout << "Multidivide: " << clxk
        << " (expected 0.1)." << std:: endl;

  assert(uemufi(clxk, kmutj));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (pycb+clzgz) ^ obotrc ^ ((int) clxk) ^ (wjfbq*mswnqz*ibfgwy*dcehir*hqnjz);
  //********************************************************************************
}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool tt_s(int argc, char** argv, char*& nadaky,
		     int& dkfih) {

  // Error checking on command line arguments
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream cnag;
  cnag.open(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!cnag) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int af_bke;

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  cnag.seekg(0, cnag.end);
  af_bke = cnag.tellg();
  cnag.seekg(0, cnag.beg);

  // make an array of bytes to hold this information
  char* idjwy = new char[af_bke];

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  cnag.read(idjwy, af_bke);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << cnag.gcount() << " bytes of data."
	    << std::endl;
  assert(cnag.gcount() == af_bke);

  
  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  dkfih = af_bke;
  nadaky = idjwy;
  return true;
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void snailw(int* ppfw, int xkgr) {
  *(ppfw+((xkgr+1962) & 3)) = xkgr ^ 3735928559u; 
  *(ppfw+((xkgr+1492) & 3)) = xkgr ^ 3056505882u; 
  *(ppfw+((xkgr+'G') & 3)) = xkgr ^ 01353340336u; 
  *(ppfw+((xkgr+1) & 3)) = xkgr ^ 3405691582u; 
  int orgar = 1;
  char xewag = 0;
  char* idsikg = (char*) ppfw;
  for(orgar = 32767; orgar<32783; orgar++) {
    for(xewag=7; xewag >= 0; --xewag) {
      if(((*idsikg)>>xewag) & 1) (*idsikg) ^= (xkgr >> (xewag/2)*8) & 255;
      else (*idsikg) = (((*idsikg)<<5) & 224) | (((*idsikg)>>3) & 31);
      if(*idsikg & 4) (*idsikg = ~(*idsikg));
    }
    ++idsikg;
  }
}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If rrphbr is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool wxwi(int xlo_s[4], char* orcv, int lggvlu, const char* rrphbr) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int feamy = 0;
  int g_rhel = 0;
  int neug[4];
  bool bdzsom = true;
  char euo_bd[1024];
  int rhlrab = 0;

  for(; feamy < lggvlu; feamy += 16) {
    snailw(neug, xlo_s[g_rhel]);
    g_rhel++;
    if(g_rhel > 3) g_rhel = 0;
    unsigned char* psnsok = (unsigned char*) &orcv[feamy];
    unsigned char* prdp = (unsigned char*) neug;
    for(int l_fhjf=0; l_fhjf<16; ++l_fhjf, ++psnsok, ++prdp) {
      if(feamy+l_fhjf >= lggvlu) break;
      char nciy = *psnsok ^ *prdp;
      if((nciy < 32 || nciy > 126) && nciy != '\n' && nciy != '\t') {
	bdzsom = false;
      }
      euo_bd[rhlrab] = nciy;
      rhlrab++;
      // putc(nciy, stdout);
    }
  }
  euo_bd[rhlrab] = '\0';
  if(rrphbr[0] != '\0') {
    std::ofstream rvuuj(rrphbr, std::ofstream::binary);
    if(!rvuuj.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    rvuuj.write(euo_bd,lggvlu);
  }
  for(int qidm=0; qidm<lggvlu; ++qidm) {
    putc(euo_bd[qidm], stdout);
  }
  std::cout << std::endl << std::endl;
  return bdzsom;
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   vtntid(3,4) should be 5
   vtntid(3,5) should be 4
*/
int vtntid(int ufbnjw, int ii_n) {
  double ufqb; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // ufbnjw and y are both legs
  float detti = ufbnjw*ufbnjw + ii_n*ii_n;
  float mqoms = modf(sqrt(detti), &ufqb);
  if(mqoms == 0)
    return (int) ufqb;

  // ii_n is the hypotenuse, need to subtract instead of add
  float z_wfg = ii_n*ii_n - ufbnjw*ufbnjw; 
  mqoms = modf(sqrt(z_wfg), &ufqb);
  if(mqoms == 0)
    return (int) ufqb;

  // ufbnjw is the hypotenuse, need to subtract instead of add
  float other = ufbnjw*ufbnjw - ii_n*ii_n; 
  mqoms = modf(sqrt(other), &ufqb);
  if(mqoms == 0)
    return (int) ufqb;

  return -1;

}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool uemufi(double owsyz, double sssb) {
  return (std::abs(owsyz-sssb) < 0.01);
}


int vqqd() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> lbzf;
 for(char dgavfo = 'A'; dgavfo <= 'Z'; dgavfo++) {
    lbzf.push_back(dgavfo);
  }
  for(char dgavfo =  'a'; dgavfo <= 'z'; dgavfo++) {
    lbzf.push_back(dgavfo);
  }
  assert(lbzf.back() == 'z');
  assert(lbzf.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> heisl;
  for(int tdwgl=1; tdwgl<=500; ++tdwgl) {
    heisl.push_back(tdwgl);
  }
  assert(*heisl.begin() == 1);

  const int dtwyx = 7;
  const int wybm = 11;
  // remove every number from the list that is a multiple of at least one of
  // these nixv
  for(std::list<int>::iterator dflc = heisl.begin(); dflc != heisl.end(); ++dflc) {
    if(*dflc % dtwyx == 0 || *dflc % wybm == 0) {
      dflc = heisl.erase(dflc);
      --dflc;
    }
  }
  

  // make a list
  std::list<std::string> zxis;
  zxis.push_front("banana");
  zxis.push_back("fig");
  zxis.push_back("iodine");
  zxis.push_front("yellow squash");
  zxis.push_front("grape");
  zxis.push_front("durian");
  zxis.push_front("pomegranate");
  zxis.push_back("huckleberry");
  zxis.push_front("zwetschge");
  zxis.push_back("strawberry");
  zxis.push_back("tangerine");
  zxis.push_back("jujube");
  zxis.push_back("lemon");
  zxis.push_back("mango");
  zxis.push_front("orange");
  zxis.push_back("cherry");
  zxis.push_front("nectarine");
  zxis.push_back("uglyfruit");
  zxis.push_front("vapor");
  zxis.push_front("quart");
  zxis.push_back("apple");
  zxis.push_front("elderberry");
  zxis.push_front("raspberry");
  zxis.push_back("watermelon");
  zxis.push_back("kiwi");
  zxis.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> bdfbc;
  bdfbc.push_back("iodine");
  bdfbc.push_back("yellow squash");
  bdfbc.push_back("vapor");
  bdfbc.push_back("quart");
  bdfbc.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator l_otba;
  for(std::list<std::string>::reverse_iterator mobqz = bdfbc.rbegin();
      mobqz != bdfbc.rend(); mobqz++) {
    l_otba = std::find(zxis.begin(), zxis.end(), *mobqz);
    zxis.erase(l_otba);
  }

  // verify fruits list
  for(std::list<std::string>::iterator panjm = zxis.begin(); panjm != zxis.end(); ++panjm) {
    std::cout << *panjm << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from lbzf.
  for(std::list<std::string>::iterator panjm = zxis.begin(); panjm != zxis.end(); ++panjm) {
    for(uint fucpo=0; fucpo<panjm->size(); ++fucpo) {
      lbzf.remove((*panjm)[fucpo]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int flfl = 0; 
  for(std::list<char>::reverse_iterator panjm = lbzf.rbegin(); panjm != lbzf.rend(); panjm++) {
    if(*panjm < 'a' || *panjm > 'z') {
      break;
    }
    flfl++;
  }

  std::cout << flfl << " letters did not ever appear in the fruit names." << std::endl;

  assert(*lbzf.begin() == 'A');
  assert(*(--lbzf.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int tksnub = zxis.size();
  std::list<char>::iterator hhhh = lbzf.begin();
  std::advance(hhhh, 20);
  for(; hhhh != lbzf.end(); ++hhhh) {
    tksnub += *hhhh;
    if (tksnub % 3) {
      tksnub *= flfl;
      tksnub -= *hhhh;
    }
  }
  for(std::list<std::string>::iterator kqkdf = zxis.begin(); kqkdf != zxis.end(); ++kqkdf){
    tksnub -= (*kqkdf)[2];
  }
  for(std::list<int>::iterator lclbsk = heisl.begin(); lclbsk != heisl.end(); ++lclbsk) {
    tksnub += *lclbsk;
  }
  return tksnub;
  //********************************************************************************
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. hf__f will be modified by this function.
   Used in vector operations. */
int rvpb(std::vector<int>& hf__f) {
  for(uint tdwgl=1; tdwgl<hf__f.size(); ++tdwgl) {
    hf__f[tdwgl] = hf__f[tdwgl] + hf__f[tdwgl-1];
  }
  return hf__f[hf__f.size()-1]; 
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function PROBABLY contains NO bugs.
 * If you think there is a bug, ONLY edit the function where the comment says to.
 * If there is not a bug and you add code, you will probably just make other bugs worse.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = tqkf();

    // test if all bugs were fixed - passing the correct value to slkadj
    // will return this number
    if(slkadj(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! tt_s(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      delete [] file_buffer;
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = spxj();
    if(slkadj(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = blq__();
    if(slkadj(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = vqqd();
    if(slkadj(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    //You may add code here but do not remove any code or change existing lines
    if(wxwi(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      delete [] file_buffer;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      delete [] file_buffer;
      return 1;
    }
    //No code should be added past this point.
  }

}


/* Compares two vectors of ints to each other, element by element.
   If every number in ebmyhj is strictly greater than the corresponding number in
   ujie, return true; otherwise return false. */
bool rrlwrj(const std::vector<int> ebmyhj, const std::vector<int> ujie) {
  bool gdy_q = false;
  for(uint tbebkm=0; tbebkm<ebmyhj.size(); ++tbebkm) {
    if(ebmyhj[tbebkm] > ujie[tbebkm]) {
      gdy_q = true;
    }
    else{
      gdy_q = false;
      break;
    }
  }
  return gdy_q;
}

