#include "ClassBreakpoint.hpp"



using namespace std;




/**
Classe permettant de réaliser l'étape 3 c'est à dire de trouver
les points d'arrets.
*/
ClassBreakpoint::ClassBreakpoint(list < list<int> > sequence)
{
  m_sequences = sequence;
}


/**
Pour chaque sequence on utilise la methode BreakpointSequence
pour trouver des points d'arrets
*/
void ClassBreakpoint::Breakpoint() {
  std::cout << "recherche de points d'arrets de la liste de sequences FLT3 : " << '\n';
  list<list<int>>::iterator itr;
  for (itr=m_sequences.begin(); itr != m_sequences.end(); itr++)
  {
    list<int> sequence = *itr;
    BreakpointSequence(sequence);
  }
  std::cout << "Recherche des points d'arrets fini !" << "\n\n";
}


/**
Permet de trouver un possible point d'arret sur la sequence
en parametre et la stocker dans la hashmap m_result
*/
void ClassBreakpoint::BreakpointSequence(list<int> sequence) {
  list<int>::iterator it;

  int inGroupOfN               = 0;
  int nbInGroupOfN             = 0;
  int elementMemoirePrecedent  = -1;
  int elementMemoire           = -1;

  for (it=sequence.begin(); it != sequence.end(); it++)
  {
    int element = *it;
    if(element == -1) {
      inGroupOfN = 1;
      nbInGroupOfN++;
      if(elementMemoire != -1) {
        elementMemoirePrecedent = elementMemoire;
      }
    }
    else{
      if(inGroupOfN == 1) {
        analyse(elementMemoirePrecedent, element, nbInGroupOfN);
        nbInGroupOfN = 0;
        inGroupOfN = 0;
      }
    }

    elementMemoire = element;
  }

}

/**
Permet de cibler sur la sequence, la partie qui contient
les "N" avec l'élement avant et après.
Cela nous permet de determiner si la défaillance est une
mutation ou une duplication en tandem avec la formule
elementPrecedent + nbDeN + 1 == elementSuivant (mutation)

s1 = 170 N N N N N N N N 179
s2 = 170 N N N N N N N N 139

s1 est une mutation car 170 + 8 + 1 = 179
s2 n'est pas une mutation car 170 + 8 + 1 != 139
  donc une possible duplication en tandem
*/
void ClassBreakpoint::analyse(int elementMemoirePrecedent, int elementMemoireSuivant, int nbInGroupOfN) {
  if(elementMemoireSuivant == -1 || elementMemoirePrecedent == -1 || elementMemoirePrecedent == -1) {
    return;
  }
  if(elementMemoirePrecedent + nbInGroupOfN + 1 == elementMemoireSuivant) {
    // mutation
  }
  else{
    std::string key = std::to_string(elementMemoirePrecedent)+"-"+std::to_string(elementMemoireSuivant)+"-"+std::to_string(nbInGroupOfN);
    if(m_result[key] == 0) {
      BreakPoint *bp = new BreakPoint(elementMemoirePrecedent,
                                      elementMemoireSuivant,
                                      nbInGroupOfN);
      m_result[key] = bp;
    }
    else{
      m_result[key]->addPoint();
    }

  }
}


std::map<std::string, BreakPoint*> ClassBreakpoint::getMap() {
  return m_result;
}
