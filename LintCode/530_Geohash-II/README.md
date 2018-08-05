用一个string base32Map来表示具体编码就可以了。
比如说11100 -> W, 11101 ->X。
string.find('W')会返回28, string.find('X')会返回29。
另外要注意isLongTurn的翻转是全局有效，而不是仅对某个5-digit的字母有效。 