class Solution:
    def defangIPaddr(self, address: str) -> str:
        defanged = ""
        for letter in address:
            if letter == '.':
                defanged += "[.]"
            else:
                defanged += letter

        return defanged
