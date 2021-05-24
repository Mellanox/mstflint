#!/usr/bin/python
### imports ###
import os
import subprocess
import argparse

def buildTree( linesList, tabIndex, nodeSons ):
    if len(linesList) == 0:
        return ("" , nodeSons)
    nodeStr = linesList[0]
    if not isNodeStr(nodeStr):
        return buildTree( linesList[1:], tabIndex, nodeSons )
    nodeTab = getNodeTab(nodeStr)
    if nodeTab == tabIndex:
        return (nodeSons, linesList)
    if (tabIndex - nodeTab) == 1:
        nodeName=getNodeName(nodeStr)
        remineLines, nodeSons = buildTree(linesList[1:], nodeTab, [] )
        nodeStruct={ 'nodeName' : nodeName ,  'nodeSons' : nodeSons }
        return buildTree( linesList[1:], nodeTab, nodeSons.add(nodeStruct) )

def isNewNode(line, queryCommand):
    if queryCommand:
        if ":" in line:
            index  = line.find(":")
            charBF = line[index-1]
            return (charBF == "" or charBF == " ")
    removeLeadingZero = line.strip(" ")
    if removeLeadingZero and removeLeadingZero[0] == "-":
        return True
    return False

def isInfoFlag(line):
    if line[0] != " " and line[0] != "-":
        return True
    return False

def keepOnlyNodes(filesList):
    helpLineOnlyNodes=[]
    onNodedescription = False
    queryCommand = False
    node=""
    for line in filesList:
        if line.strip(" ") == "" or line == '\n':
            continue
        if "Examples" in line:
            helpLineOnlyNodes.append(node)
            return helpLineOnlyNodes
        if "COMMANDS SUMMARY" in line:
            queryCommand = True
            continue
        if isInfoFlag(line):
            queryCommand = False
            onNodedescription = False
            continue
        if isNewNode(line, queryCommand):
            if node!= "":
                helpLineOnlyNodes.append(node)
            onNodedescription = True
            node=line
            if ":" not in line:
                node=node+" :"
            continue
        if onNodedescription:
            node=node+" " + line.strip(" ")
    helpLineOnlyNodes.append(node)
    return helpLineOnlyNodes


#-l |--loopback   <loopback>             : Configure Loopback Mode [NO(no loopback)/PH(phy loopback)/EX(external loopback)]

def isShortCutsLine(line):
    if "|" in line:
        lineSplit=line.split("|")[0].strip(" ")
        lineSpaceSplit=lineSplit.split(" ")
        lineSpaceWords = list(filter( lambda x: x != "" ,lineSpaceSplit))
        return (len(lineSpaceWords) <= 1)
    return False

def getNodeShortCutsAndName(line):
    shortCuts=""
    name=""
    line = line.strip(" ")
    if isShortCutsLine(line):
        lineSplit = line.split("|")
        rightFlag=lineSplit[0].strip(" ")
        leftFlag=lineSplit[1].strip(" ").split(" ")[0]
        if len(rightFlag) > len(leftFlag):
            return leftFlag, rightFlag
        else:
            return rightFlag, leftFlag
    name=line.split(" ")[0]
    return shortCuts, name

def getSonsAndUpperNeededFromVals(sonsValsSplit):
    upperNeed="1"
    sons=""
    lastVal=""
    if "..." in sonsValsSplit:
        threePointsIndex = sonsValsSplit.index("...")
        if threePointsIndex < len(sonsValsSplit)-1:
            numBefore = int(sonsValsSplit[threePointsIndex-1]) + 1
            numAfter  = int(sonsValsSplit[threePointsIndex+1])
            arr=range(numBefore,numAfter)
            sonsValsSplit[threePointsIndex] = " ".join(map(lambda x : str(x), arr))
    for val in sonsValsSplit:
        sonVal = val.split('(')[0]
        sons=sons+ " " + sonVal
        if not sonVal.isupper():
            upperNeed=""
    return sons, upperNeed

def getSonsValsFromLine(line):
    ret=""
    lineSplit = line.split("[")[1:]
    for sons in lineSplit:
        ret=ret + sons.split("]")[0]
    return ret

def getNodeTypeSonsUpperNeedAndLastCommandIndex(line):
    lastCommandIndex="-1"
    sons=""
    nodeType="0"
    upperNeed=""
    if "[" in line:
        lastCommandIndex="1"
        sonsVals=getSonsValsFromLine(line)
        sonsValsSplit=[]
        if "/" in sonsVals:
            nodeType="3"
            sonsValsSplit=sonsVals.split("/")
        elif "," in sonsVals:
            nodeType="4"
            sonsValsSplit=sonsVals.split(",")
        else:
            nodeType="3"
            sonsValsSplit=[sonsVals]
        sons, upperNeed = getSonsAndUpperNeededFromVals(sonsValsSplit)
    return nodeType, sons, upperNeed, lastCommandIndex

def parseLine(line):
    node={ 'shortCut': "" , 'name' : "" , 'lastCommandIndex' : "" , 'nodeType' :  "" , 'sons' : "" , 'extra' : "" , 'upperNeed' : "" , 'description' : "" }
    lineSplitByColoumn = line.split(":")
    shortCut, name = getNodeShortCutsAndName(lineSplitByColoumn[0])
    node["shortCut"]=" ".join(shortCut.split())
    node["name"] =" ".join(name.split())
    node["description"]=lineSplitByColoumn[1]
    nodeType,sons,upperNeed,lastCommandIndex = getNodeTypeSonsUpperNeedAndLastCommandIndex(line)
    node["nodeType"]=nodeType
    node["sons"]=sons
    node["upperNeed"]=upperNeed
    node["lastCommandIndex"]=lastCommandIndex
    return node

def getNumOfLeadingZeroFromLine(line):
    count=0
    for char in line:
        if char == " ":
            count+=1
        elif char == "\t":
            count+=4
        else:
            return count
    return count

def getTabLevelFromLine(line):
    numOfLeadingZeros = getNumOfLeadingZeroFromLine(line)
    return int(numOfLeadingZeros / 4)

def getUserInput():
    my_parser = argparse.ArgumentParser()
    my_parser.add_argument('-n','--name', action='store', type=str ,  help="Tool Name", required=True)
    my_parser.add_argument('-o','--output',  action='store', type=int, default=1, choices=[1],  help="Output: 1- build structs for Auto-Compeletion(Default)")
    my_parser.add_argument('-c','--command',  action='store', type=str, default="", help="Full Command Line: ")

    args = my_parser.parse_args()
    return vars(args)

def isCommandNode(node):
    return node["name"][0] != "-"

def isNeedUpdateNode(prevNode, prevIndex, currNode, CurrIndex):
    if prevNode == None:
        return True
    if isCommandNode(prevNode):
        if isCommandNode(currNode):
            return prevIndex > CurrIndex
        else:
            return False
    else:
        return CurrIndex > prevIndex

def buildMSTNodesTree(commandLine):
    nodesTree=[]
    filesList = subprocess.check_output("sudo mst help", shell=True).decode().split("\n")
    options=""
    params=""
    sons=""
    extra=""
    lastNodeStruct={ 'shortCut': "" , 'name' : "" , 'lastCommandIndex' : "-1" , 'nodeType' :  "0" , 'sons' : "" , 'extra' : "" , 'upperNeed' : "" , 'description' : ""}
    mstMainNodeSons=""
    for line in reversed(filesList):
        lineRemovingLeadingZero = line.strip(" ")
        if len(lineRemovingLeadingZero) == 0:
            continue
        if lineRemovingLeadingZero[0:3] == "mst":
            splitLine = lineRemovingLeadingZero[4:].split(" ")
            nodeName=splitLine.pop(0)
            if nodeName not in mstMainNodeSons:
                mstMainNodeSons = mstMainNodeSons +  " " + nodeName
            if nodeName not in commandLine.split(" "):
                continue
            if lastNodeStruct["name"] != nodeName:
                if lastNodeStruct["name"] != "" and lastNodeStruct["sons"].strip(" ") != "":
                    nodesTree.append(lastNodeStruct)
                lastNodeStruct={ 'shortCut': "" , 'name' : nodeName , 'lastCommandIndex' : "-1" , 'nodeType' :  "0" , 'sons' : "" , 'extra' : "" , 'upperNeed' : "" , 'description' : ""}
            for son in reversed(splitLine):
                if son[0] == "<":
                    continue
                if son[0] == "[":
                    sonName=son.replace("[", "").replace("]","")
                    if sonName == "OPTIONS":
                        extra=extra+options+sons
                        sons=""
                    elif sonName == "params":
                        extra=params
                    else:
                        sons=sons+" "+sonName
                else:
                    if sons != "":
                        nodesTree.append({ 'shortCut': "" , 'name' : son , 'lastCommandIndex' : "-1" , 'nodeType' :  "0" , 'sons' : sons , 'extra' : extra , 'upperNeed' : "" , 'description' : ""})
                    sons=son
                    params=""
                    options=""
            lastNodeStruct["sons"]= lastNodeStruct["sons"] + " " +   sons
            sons=""
            params=""
            options=""
        elif "params:" in line:
            paramsSplit = lineRemovingLeadingZero.split(" ")
            for param in paramsSplit:
                if param[0] == "[":
                    paramMame = param.replace("[", "").replace("]","")
                    params=params + " " + paramMame
        elif lineRemovingLeadingZero[0] == "-":
            options=options + " " + lineRemovingLeadingZero.split(" ")[0].replace(":", "")
    nodesTree.append(lastNodeStruct)
    nodesTree.append({ 'shortCut': "" , 'name' : "mst" , 'lastCommandIndex' : "-1" , 'nodeType' :  "0" , 'sons' : mstMainNodeSons , 'extra' : "" , 'upperNeed' : "" , 'description' : ""})
    return nodesTree

def buildMFTTollNodesTree(toolName,commandLine):
    nodesTree=[]
    nodesTabs=["","","","","","","","","","","","","","","","","","",""]
    filesList = subprocess.check_output(toolName + " -h", shell=True).decode().split("\n")
    helpLineOnlyNodes = keepOnlyNodes(filesList)
    tabLevel=0
    tabLevelBestIndex = [0] * 8
    tabLevelBestNode  = [None] * 8
    for line in reversed(helpLineOnlyNodes):
        parsedLine = parseLine(line)
        tabLevel = getTabLevelFromLine(line)
        nodesTabs[tabLevel] = nodesTabs[tabLevel] + " " + parsedLine["name"]
        sons = nodesTabs[tabLevel+1]
        nodesTabs[tabLevel+1]=""
        if parsedLine["sons"] == "":
            parsedLine["sons"]=sons
        else:
            parsedLine["extra"]=sons
        flagIndex = -1
        splitCommand = commandLine.split(" ")
        if parsedLine["name"] in splitCommand:
            flagIndex = splitCommand.index(parsedLine["name"])
        elif parsedLine["shortCut"] in splitCommand and parsedLine["shortCut"] != "":
            flagIndex =  splitCommand.index(parsedLine["shortCut"])
        if flagIndex > -1:
            if isNeedUpdateNode(tabLevelBestNode[tabLevel], tabLevelBestIndex[tabLevel], parsedLine, flagIndex):
                tabLevelBestNode[tabLevel] = parsedLine
                tabLevelBestIndex[tabLevel]= flagIndex
                for i in range(tabLevel+1, 8):
                    if tabLevelBestIndex[i] < flagIndex:
                        tabLevelBestNode[i] = None
    for bestTab in tabLevelBestNode:
        if bestTab != None:
            nodesTree.append(bestTab)

    nodesTree.append({ 'shortCut': "" , 'name' : toolName , 'lastCommandIndex' : "-1" , 'nodeType' :  "0" , 'sons' : " ".join(nodesTabs) , 'extra' : "" , 'upperNeed' : "" , 'description' : ""})
    return nodesTree

def buildNodesTree(toolName,commandLine):
    if toolName == "mst":
        return buildMSTNodesTree(commandLine)
    else:
        return buildMFTTollNodesTree(toolName,commandLine)


def buildShortCutsNodeListNodesDeclary(nodesTree):
    shortCuts=""
    nodesList=""
    nodesDeclareArray = []
    for node in nodesTree:
        shortCutVal  = node["shortCut"]
        nodeNAme     = node["name"]
        nodeSons     = node["sons"]
        if nodeNAme == "--device" or nodeNAme == "-d" or nodeNAme == "-dev" or shortCutVal == "-d":
            nodeSons="temp"
            node["lastCommandIndex"]="1"
            node["nodeType"]="2"
        if shortCutVal != "":
            shortCuts=shortCuts + " [\"" + shortCutVal + "\"]=\"" + nodeNAme + "\""
        if nodeSons != "":
            nodesList=nodesList + " " + nodeNAme
            nodeDeclare="declare -A "+ nodeNAme.replace("-", "")+"=( [\"lastCommandIndex\"]="+node["lastCommandIndex"]+" [\"nodeType\"]=\""+node["nodeType"]+"\" [\"sons\"]=\""+nodeSons+"\" [\"extra\"]=\""+node["extra"]+"\" [\"upperNeed\"]="+node["upperNeed"]+" )\n"
            nodesDeclareArray.append(nodeDeclare)
    return shortCuts,nodesList,nodesDeclareArray

def printNodesStructures(nodesTree):
    shortCuts,nodesList,nodesDeclareArray = buildShortCutsNodeListNodesDeclary(nodesTree)

    print ("declare -A shortcuts=( " + shortCuts + " )\n")
    print ("nodes=\""+nodesList+"\"\n")
    for declareLine in nodesDeclareArray:
        print (declareLine)


if __name__ == "__main__":
    userInput = getUserInput()
    toolName=userInput["name"]
    commandLine=userInput["command"]

    nodesTree = buildNodesTree(toolName,commandLine)

    printNodesStructures(nodesTree)
