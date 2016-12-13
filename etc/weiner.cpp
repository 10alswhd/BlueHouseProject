#include <string>
#include <map>
const int MAXLEN = 600000;
std::string s;
int pos[MAXLEN], len[MAXLEN], par[MAXLEN];
std::map<char,int> to[MAXLEN], link[MAXLEN];
int sz = 2;
int path[MAXLEN];

void attach(int child, int parent, char c, int child_len) {
  to[parent][c] = child;
  len[child] = child_len;
  par[child] = parent;
}

void extend(int i) {
  int v, vlen = s.size() - i, old = sz - 1, pstk = 0;
  for (v = old; !link[v].count(s[i]); v = par[v]) {
    vlen -= len[v];
    path[pstk++] = v;
  }
  int w = link[v][s[i]];
  if (to[w].count(s[i + vlen])) {
    int u = to[w][s[i + vlen]];
    for (pos[sz] = pos[u] - len[u]; s[pos[sz]] == s[i + vlen]; pos[sz] += len[v]) {
      v = path[--pstk];
      vlen += len[v];
    }
    attach(sz, w, s[pos[u] - len[u]], len[u] - (pos[u] - pos[sz]));
    attach(u, sz, s[pos[sz]], pos[u] - pos[sz]);
    w = link[v][s[i]] = sz++;
  }
  link[old][s[i]] = sz;
  attach(sz, w, s[i + vlen], s.size() - (i + vlen));
  pos[sz++] = s.size();
}

int main() {
  len[1] = 1; pos[1] = 0; par[1] = 0;
  for (int c = 0; c <= 255; c++)
    link[0][c] = 1;
  s = "abababasdsdfasdf";
  for (int i = s.size() - 1; i >= 0; i--)
    extend(i);
}
