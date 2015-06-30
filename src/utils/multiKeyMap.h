#ifndef MULTIKEYMAP_H
#define MULTIKEYMAP_H
class key{
public:
    long unsigned int x_, y_;
    key( long unsigned int x, long unsigned int y): x_(x), y_(y){
    }
    friend bool operator < (const key& kl, const key& kr);

};
#endif //MULTIKEYMAP_H
