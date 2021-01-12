#ifndef HASH_H
#define HASH_H

uint32_t hash(uint32_t n){
	uint32_t ret = 0;
	ret += ((char*)&n)[0];
	ret += (ret << 10);
	ret ^= (ret >> 6);
	ret += ((char*)&n)[1];
	ret += (ret << 10);
	ret ^= (ret >> 6);
	ret += ((char*)&n)[2];
	ret += (ret << 10);
	ret ^= (ret >> 6);
	ret += ((char*)&n)[3];
	ret += (ret << 10);
	ret ^= (ret >> 6);
  ret += (ret << 3);
  ret ^= (ret >> 11);
  ret += (ret << 15);
  return ret;
}

#endif
