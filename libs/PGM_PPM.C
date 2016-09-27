
template <typename T>
char* PGM_PPM<T>::_readitem(ifstream& file, char* buffer){
  char *word;
  char c;
  int k;

  k = 0;
  word = buffer;
  
  // Récupère le premier mot à partir du pointeur du stream
  while(!file.eof()){
    file.get(c);
    *word = c;

    switch(k){
      case 0:
        if (*word=='#') k=1;
        if (isalnum(*word)) k=2, word++;
        break;
      case 1:
        if (*word==0xA) k=0;
        break;
      case 2:
        if (!isalnum(*word)) {
	        *word = 0;
          return buffer;
        }
        word++;
        break;
    }
  }
  *word=0;
  return buffer;
}

template <typename T>
void PGM_PPM<T>::loadImage(char* filename){

  long height, width, grey;
  T **m;

  //Lire le fichier
  ifstream file;

  char *buffer;
  int i;
  
  buffer = (char*) calloc(80, sizeof(char));
 
  file.open(filename);
  if (!file.is_open())
    cerr << "ouverture du fichier\"" << filename << "\" impossible" << endl;


  _readitem(file, buffer);

  if( !( strcmp(buffer, "P5") == 0 || strcmp(buffer, "P6") == 0 ) )
    cerr << "entete du fichier '" << buffer << "' invalide" << endl;

  width  = atoi(_readitem(file, buffer));
  height = atoi(_readitem(file, buffer));
  grey   = atoi(_readitem(file, buffer));

  _nrl = 0;
  _nrh = height - 1;
  _ncl = 0;
  _nch = width - 1;
  m = buildMatrix();

  free(buffer);
  buffer = new char[width];

  for(i=0; i<height; i++){
    if (is_same<T, rgb8>::value){
        file.read((char*)m[i], 3*sizeof(byte)*width);
    } else {
        file.read((char*)m[i], width);
    }
  }
  
  free(buffer);

  _matrix = m;

  file.close();

}

template <typename T>
void PGM_PPM<T>::saveImage(T** matrix, char* filename){

long nrow = _nrh - _nrl + 1;
long ncol = _nch - _ncl + 1;

char* buffer = new char[80];
  
  ofstream file;
  int  i;

  file.open(filename);
  if (!file.is_open())
    cerr << "ouverture du fichier impossible" << endl;

  // enregistrement de l'image au format voulue
  if (is_same<T, rgb8>::value){
    sprintf(buffer,"P6\n%ld %ld\n255\n",ncol, nrow);
  } else {
    sprintf(buffer,"P5\n%ld %ld\n255\n",ncol, nrow);
  }
  file.write(buffer, strlen(buffer));
  for(i=_nrl; i<=_nrh; i++)
    if (is_same<T, rgb8>::value){
      file.write((char*)(&matrix[i][_ncl]), 3*sizeof(byte)*ncol);
    } else {
      file.write((char*)(&matrix[i][_ncl]), ncol);
    }

  // fermeture du fichier 
  file.close();

}

template <typename T>
T** PGM_PPM<T>::buildMatrix(){
  long nrow=_nrh-_nrl+1, ncol=_nch-_ncl+1;
  T **m;
  
  if (is_same<T, rgb8>::value){
    m = new T * [nrow];
  } else {
    m = new T * [nrow+NR_END];
  }

  //Initialise les pointeurs à NULL
  fill_n( m, nrow, static_cast<T*>( 0 ) ); 
  
  //Initialise l'allocation memoires des colonnes
  for ( int row = 0; row < nrow; ++row) { 
      if (is_same<T, rgb8>::value){
        m[row] = new T[ncol];
      } else {
        m[row] = new T[ncol+NR_END];
      }
  }

  _matrix = m;

  return m;
}

template <typename T>
byte** PGM_PPM<T>::rgb8tobmatrix(rgb8** matrix){
  long nrow=_nrh-_nrl+1, ncol=_nch-_ncl+1;
  byte** m;

  m = new byte * [nrow];
  fill_n( m, nrow, static_cast<byte*>( 0 ) );

  for ( int row = 0; row < nrow; ++row)
    m[row] = new byte[ncol];
    
  for(int i=0; i<nrow; i++)
    for(int j=0; j<ncol; j++)
      m[i][j] = (matrix[i][j].r + matrix[i][j].g + matrix[i][j].b)/3;

  return m;     
}
