import cluster as clucore
import copy


class Data:
    def __init__(self, InitList, strHOList, strCOList, coefHOList, coefCOList, trackList, maxOPLen):
        """
        :param InitList: 初始表
        :param strHOList: 字符形式的HO列表
        :param strCOList: 字符形式的CO列表
        :param coefHOList: HO系数的列表
        :param coefCOList: CO系数的列表
        :param trackList: tracking operator的字符形式HO列表
        :param maxOPLen: 最大operator长度
        """
        # deriveData的存储
        self.__deriveData = None
        # 从数字到字母的映射表
        self.__numToLetterMap = [None] * 53
        # 从字母到数字的映射表
        self.__letterToNumMap = [None] * 52
        # 数字形态的Hamilton operator列表
        self.__numHOList = []
        # 数字形态的Collapse operator列表
        self.__numCOList = []
        # 现在的Hamilton operator列表系数表
        self.__coefHOList = []
        # 现在的Collapse operator列表系数表
        self.__coefCOList = []
        # tracking operator列表
        self.__numTrackList = []
        # 最大算符长度
        self.__maxOPLen = maxOPLen

        self.__CreateNumLetterMap(strHOList, strCOList, trackList)
        (self.__numHOList, self.__numCOList, self.__numTrackList) = \
            self.__MapLetterListToNumList(strHOList, strCOList, trackList)
        self.__coefHOList = copy.deepcopy(coefHOList)
        self.__coefCOList = copy.deepcopy(coefCOList)
        # 检查系数列表中的类型
        for c in coefHOList:
            if not isinstance(c, int) and not isinstance(c, float) and not isinstance(c, complex):
                raise TypeError("Invalid types in coefficient list.")
        for c in coefCOList:
            if not isinstance(c, int) and not isinstance(c, float) and not isinstance(c, complex):
                raise TypeError("Invalid types in coefficient list.")
        for c in InitList:
            if not isinstance(c, int) and not isinstance(c, float) and not isinstance(c, complex):
                raise TypeError("Invalid types in coefficient list.")
        if not isinstance(self.__maxOPLen, int):
            raise TypeError("Invalid types for maxOPLen.")

        self.__deriveData = clucore.DeriveAssign(InitList, self.__numHOList, self.__coefHOList,
                                                 self.__numCOList, self.__coefCOList, self.__numTrackList, maxOPLen)

    def SetCoefHOList(self, coefHOList):
        """
        :param coefHOList: HO系数的列表
        """
        for c in coefHOList:
            if not isinstance(c, int) and not isinstance(c, float) and not isinstance(c, complex):
                raise TypeError("Invalid types in coefficient list.")
        self.__coefHOList = copy.deepcopy(coefHOList)
        clucore.SetHamiltonCoef(self.__deriveData, self.__coefHOList)

    def SetCoefCOList(self, coefCOList):
        """
        :param coefCOList: CO系数的列表
        """
        for c in coefCOList:
            if not isinstance(c, int) and not isinstance(c, float) and not isinstance(c, complex):
                raise TypeError("Invalid types in coefficient list.")
        self.__coefCOList = copy.deepcopy(coefCOList)
        clucore.SetCollapseCoef(self.__deriveData, self.__coefCOList)

    def SetCurrentValue(self, curValueList):
        """
        :param curValueList: current value的列表
        """
        for c in curValueList:
            if not isinstance(c, int) and not isinstance(c, float) and not isinstance(c, complex):
                raise TypeError("Invalid types in coefficient list.")
        clucore.SetCurrentValue(self.__deriveData, curValueList)

    def GetStrHOList(self):
        """
        :return: 字符形式的HO列表
        """
        ans = []
        for numlist in self.__numHOList:
            strname = self.__MapNumListToStr(numlist)
            ans.append(strname)
        return ans

    def GetStrCOList(self):
        """
        :return: 字符形式的CO列表
        """
        ans = []
        for numlist in self.__numCOList:
            strname = self.__MapNumListToStr(numlist)
            ans.append(strname)
        return ans

    def GetNumHOList(self):
        """
        :return: 数字形式的HO列表
        """
        return copy.deepcopy(self.__numHOList)

    def GetNumCOList(self):
        """
        :return: 数字形式的CO列表
        """
        return copy.deepcopy(self.__numCOList)

    def GetCurrentValue(self):
        """
        :return: 当前的current value列表
        """
        return clucore.GetCurrentValue(self.__deriveData)

    def Calculate(self):
        """
        :return: 计算的结果, 类型为列表
        """
        return clucore.CalEvolution(self.__deriveData)

    def __CreateNumLetterMap(self, strHOList, strCOList, trackList):
        for s in strHOList:
            if not isinstance(s, str):
                raise TypeError("Invalid types in string hamilton list.")
        for s in strCOList:
            if not isinstance(s, str):
                raise TypeError("Invalid types in string collapse list.")
        for s in trackList:
            if not isinstance(s, str):
                raise TypeError("Invalid types in string tracking list.")
        # 26个字母的桶
        lettersBucket = [None] * 26
        for s in strHOList:
            for letter in s.upper():
                lettersBucket[ord(letter) - 65] = letter
        for s in strCOList:
            for letter in s.upper():
                lettersBucket[ord(letter) - 65] = letter
        for s in trackList:
            for letter in s.upper():
                lettersBucket[ord(letter) - 65] = letter
        totalLetters = []
        for stuff in lettersBucket:
            if stuff is not None:
                totalLetters.append(stuff)
        cnt = 0
        for c in totalLetters:
            self.__numToLetterMap[2 * cnt + 1] = c
            self.__numToLetterMap[2 * cnt + 2] = c.lower()
            self.__letterToNumMap[ord(c) - 65] = 2 * cnt + 1
            self.__letterToNumMap[ord(c) - 39] = 2 * cnt + 2
            cnt += 1

    def __MapLetterListToNumList(self, strHOList, strCOList, trackList):
        numHOList = self.__MapLetterListToNumList_Build(strHOList)
        numCOList = self.__MapLetterListToNumList_Build(strCOList)
        numTrackList = self.__MapLetterListToNumList_Build(trackList)
        return numHOList, numCOList, numTrackList

    def __MapLetterListToNumList_Build(self, strList):
        ans = []
        for s in strList:
            li = []
            for letter in s:
                if 90 >= ord(letter) >= 65:
                    li.append(self.__letterToNumMap[ord(letter) - 65])
                else:
                    li.append(self.__letterToNumMap[ord(letter) - 71])
            ans.append(li)
        return ans

    def __MapNumListToStr(self, numList):
        s = ''
        for n in numList:
            if not isinstance(n, int):
                raise TypeError("Invalid types in num list.")
            s += self.__numToLetterMap[n]
        return s
