from typing import List
from collections import defaultdict

class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        res = defaultdict(list)

        for s in strs:
            # Crée un tableau de 26 zéros pour chaque lettre a-z
            count = [0] * 26
            for c in s:
                count[ord(c) - ord('a')] += 1

            # Utilise le tuple de comptages comme clé pour grouper les anagrammes
            res[tuple(count)].append(s)

        # Retourne seulement les valeurs (les groupes d'anagrammes)
        return list(res.values())
