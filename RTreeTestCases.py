from RTree import *
from RTreeTestClass import Test

test = Test()

myTree = RTree(4,2,'random')

myTree.Insert(Value([1,1],0))
myTree.Insert(Value([2,2],1))

test.TestingSection(myTree.root, myTree.numberOfChildrenInNode)

myTree4 = RTree(4,2,'random')

for i in range(13):
    myTree4.Insert(Value([i, i], i))

test.TestingSection(myTree4.root,myTree4.numberOfChildrenInNode)

myTree2 = RTree(4,2,'random')

for i in range(14):
    if i == 5:
        myTree2.Insert(Value([i, i], i))
    else:
        myTree2.Insert(Value([i, i], i))

test.TestingSection(myTree2.root,myTree2.numberOfChildrenInNode)

myTree3 = RTree(2,3,'random')
for i in range(10000):
    myTree3.Insert(Value([i,i,i],i))

test.TestingSection(myTree3.root,myTree3.numberOfChildrenInNode)

myTree5 = RTree(4,2,'random')

for i in range(100):
    myTree5.Insert(Value([100-i,100-i],i))

test.TestingSection(myTree5.root,myTree5.numberOfChildrenInNode)