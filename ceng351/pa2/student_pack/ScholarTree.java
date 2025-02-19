import java.util.ArrayList;

public class ScholarTree {

    public ScholarNode primaryRoot;        //root of the primary B+ tree
    public ScholarNode secondaryRoot;    //root of the secondary B+ tree

    public ScholarTree(Integer order) {
        ScholarNode.order = order;
        primaryRoot = new ScholarNodePrimaryLeaf(null);
        primaryRoot.level = 0;
        secondaryRoot = new ScholarNodeSecondaryLeaf(null);
        secondaryRoot.level = 0;
    }

    public void addPaper(CengPaper paper) {
        addToPrimaryTree(paper);
        addToSecondaryTree(paper);
    }

    public CengPaper searchPaper(Integer paperId) {
        ScholarNode node = primaryRoot;
        boolean found;
        int level = 0;

        while (node.getType() == ScholarNodeType.Internal) {
            ScholarNodePrimaryIndex indexNode = (ScholarNodePrimaryIndex) node;
            int paperIdCount = indexNode.paperIdCount();
            String indentation = "\t".repeat(level);
            System.out.println(indentation + "<index>");
            for (int i = 0; i < paperIdCount; i++) {
                System.out.println(indentation + indexNode.paperIdAtIndex(i));
            }
            System.out.println(indentation + "</index>");
            found = true;
            for (int i = 0; i < paperIdCount; i++) {
                if (indexNode.paperIdAtIndex(i) > paperId) {
                    node = indexNode.getChildrenAt(i);
                    found = false;
                    break;
                }
            }
            level++;
            if (found) {
                node = indexNode.getChildrenAt(paperIdCount);
            }
        }
        ScholarNodePrimaryLeaf leafNode = (ScholarNodePrimaryLeaf) node;
        int paperCount = leafNode.paperCount();
        for (int i = 0; i < paperCount; i++) {
            String indentation = "\t".repeat(level);
            if (leafNode.paperIdAtIndex(i).equals(paperId)) {
                System.out.println(indentation + "<data>");
                System.out.print(indentation + "<record>");
                System.out.print(leafNode.paperAtIndex(i).fullName());
                System.out.print("</record>\n");
                System.out.println(indentation + "</data>");
                return leafNode.paperAtIndex(i);
            }
        }
        System.out.print("Could not find ");
        System.out.println(paperId);
        return null;
    }

    public void searchJournal(String journal) {
        ScholarNode node = secondaryRoot;
        boolean found;
        int level = 0;

        while (node.getType() == ScholarNodeType.Internal) {
            ScholarNodeSecondaryIndex indexNode = (ScholarNodeSecondaryIndex) node;
            int journalCount = indexNode.journalCount();
            String indentation = "\t".repeat(level);
            System.out.println(indentation + "<index>");
            for (int i = 0; i < journalCount; i++) {
                System.out.println(indentation + indexNode.journalAtIndex(i));
            }
            System.out.println(indentation + "</index>");
            found = true;
            for (int i = 0; i < journalCount; i++) {
                int result = indexNode.journalAtIndex(i).compareToIgnoreCase(journal);
                if (result > 0) {
                    node = indexNode.getChildrenAt(i);
                    found = false;
                    break;
                }
            }
            level++;
            if (found) {
                node = indexNode.getChildrenAt(journalCount);
            }
        }
        ScholarNodeSecondaryLeaf leafNode = (ScholarNodeSecondaryLeaf) node;
        int journalCount = leafNode.journalCount();
        for (int i = 0; i < journalCount; i++) {
            StringBuilder indentation = new StringBuilder("\t".repeat(level));
            if (leafNode.journalAtIndex(i).equals(journal)) {
                System.out.println(indentation + "<data>");
                System.out.println(indentation + leafNode.journalAtIndex(i));
                for (int j = 0; j < leafNode.getPaperIdBucket().size(); j++) {
                    ArrayList<Integer> paperIdBucket = leafNode.papersAtIndex(j);
                    indentation = new StringBuilder("\t".repeat(level + 1));
                    for (Integer integer : paperIdBucket) {
                        CengPaper currentPaper = searchPaperWithoutPrint(integer);
                        if (currentPaper.journal().equals(journal)) {
                            System.out.print(indentation + "<record>");
                            System.out.print(currentPaper.fullName());
                            System.out.print("</record>\n");
                        }
                    }
                }
                indentation = new StringBuilder("\t".repeat(level));
                System.out.println(indentation + "</data>");
                return;
            }
        }
        System.out.print("Could not find ");
        System.out.println(journal);
    }

    public void printPrimaryScholar() {
        printPrimaryScholarHelper(primaryRoot, 0);
    }

    public void printSecondaryScholar() {
        printSecondaryScholarHelper(secondaryRoot, 0);
    }

    // Extra functions if needed
    public void addToPrimaryTree(CengPaper paper) {
        ScholarNodePrimaryLeaf leafToInsert = findLeafPrimary(paper.paperId());
        ArrayList<CengPaper> papersOfLeaf = leafToInsert.getPapers();
        int maxCapacity = 2 * ScholarNode.order + 1;
        int indexToInsert = -1;

        for (int i = 0; i < leafToInsert.paperCount(); i++) {
            if (papersOfLeaf.get(i).paperId() > paper.paperId()) {
                indexToInsert = i;
                break;
            }
        }
        if (indexToInsert == -1) {
            indexToInsert = leafToInsert.paperCount();
        }

        leafToInsert.addPaper(indexToInsert, paper);

        if (leafToInsert.paperCount() == maxCapacity) {
            if (leafToInsert.getParent() == null) {
                ScholarNodePrimaryIndex newRoot = new ScholarNodePrimaryIndex(null);
                ScholarNodePrimaryLeaf newNode = new ScholarNodePrimaryLeaf(newRoot);

                for (int index = ScholarNode.order, j = 0; index < leafToInsert.paperCount(); index++, j++) {
                    newNode.addPaper(j, leafToInsert.paperAtIndex(index));
                }

                leafToInsert.getPapers().subList(ScholarNode.order, leafToInsert.getPapers().size()).clear();
                leafToInsert.setParent(newRoot);

                newRoot.addPaper(0, newNode.paperIdAtIndex(0));
                newRoot.addChild(0, leafToInsert);
                newRoot.addChild(1, newNode);

                primaryRoot = newRoot;
            } else {
                ScholarNode parentNode = leafToInsert.getParent();
                ScholarNodePrimaryIndex parentIndex = (ScholarNodePrimaryIndex) parentNode;
                ScholarNodePrimaryLeaf newNode = new ScholarNodePrimaryLeaf(parentNode);

                for (int index = ScholarNode.order, j = 0; index < leafToInsert.paperCount(); index++, j++) {
                    newNode.addPaper(j, leafToInsert.paperAtIndex(index));
                }

                leafToInsert.getPapers().subList(ScholarNode.order, leafToInsert.getPapers().size()).clear();

                Integer keyToUp = newNode.paperIdAtIndex(0);
                boolean isSet = false;
                for (int i = 0; i < parentIndex.paperIdCount(); i++) {
                    if (parentIndex.paperIdAtIndex(i) > keyToUp) {
                        parentIndex.addPaper(i, keyToUp);
                        parentIndex.addChild(i + 1, newNode);
                        isSet = true;
                        break;
                    }
                }
                if (!isSet) {
                    parentIndex.addPaper(keyToUp);
                    parentIndex.addChild(newNode);
                }

                ScholarNode nextParent;
                ScholarNodePrimaryIndex nextParentIndex;
                while (parentIndex.paperIdCount() == maxCapacity) {
                    isSet = false;

                    nextParent = parentNode.getParent();
                    nextParentIndex = (ScholarNodePrimaryIndex) nextParent;

                    if (parentNode == primaryRoot) {
                        ScholarNodePrimaryIndex newRoot = new ScholarNodePrimaryIndex(null);
                        ScholarNodePrimaryIndex newInternalNode = new ScholarNodePrimaryIndex(newRoot);

                        for (int index = ScholarNode.order + 1, j = 0; index < parentIndex.paperIdCount(); index++, j++) {
                            newInternalNode.addPaper(j, parentIndex.paperIdAtIndex(index));
                            newInternalNode.addChild(j, parentIndex.getChildrenAt(index));
                            parentIndex.getChildrenAt(index).setParent(newInternalNode);
                        }
                        newInternalNode.addChild(newInternalNode.paperIdCount(), parentIndex.getChildrenAt(parentIndex.paperIdCount()));
                        parentIndex.getChildrenAt(parentIndex.paperIdCount()).setParent(newInternalNode);

                        keyToUp = parentIndex.paperIdAtIndex(ScholarNode.order);

                        parentIndex.getAllPaperIds().subList(ScholarNode.order, parentIndex.getAllPaperIds().size()).clear();
                        parentIndex.getAllChildren().subList(ScholarNode.order + 1, parentIndex.getAllChildren().size()).clear();

                        newRoot.addPaper(0, keyToUp);
                        newRoot.addChild(0, parentNode);
                        parentNode.setParent(newRoot);
                        newRoot.addChild(1, newInternalNode);
                        primaryRoot = newRoot;
                        break;
                    } else {
                        ScholarNodePrimaryIndex newInternalNode = new ScholarNodePrimaryIndex(nextParent);
                        for (int index = ScholarNode.order + 1, j = 0; index < parentIndex.paperIdCount(); index++, j++) {
                            newInternalNode.addPaper(j, parentIndex.paperIdAtIndex(index));
                            newInternalNode.addChild(j, parentIndex.getChildrenAt(index));
                            parentIndex.getChildrenAt(index).setParent(newInternalNode);
                        }
                        newInternalNode.addChild(newInternalNode.paperIdCount(), parentIndex.getChildrenAt(parentIndex.paperIdCount()));
                        parentIndex.getChildrenAt(parentIndex.paperIdCount()).setParent(newInternalNode);

                        keyToUp = parentIndex.paperIdAtIndex(ScholarNode.order);

                        parentIndex.getAllPaperIds().subList(ScholarNode.order, parentIndex.getAllPaperIds().size()).clear();
                        parentIndex.getAllChildren().subList(ScholarNode.order + 1, parentIndex.getAllChildren().size()).clear();

                        for (int i = 0; i < nextParentIndex.paperIdCount(); i++) {
                            if (nextParentIndex.paperIdAtIndex(i) > keyToUp) {
                                nextParentIndex.addPaper(i, keyToUp);
                                nextParentIndex.addChild(i, parentNode);
                                nextParentIndex.setChild(i + 1, newInternalNode);
                                isSet = true;
                                break;
                            }
                        }
                        if (!isSet) {
                            nextParentIndex.addPaper(keyToUp);
                            nextParentIndex.addChild(newInternalNode);
                        }
                        parentNode = nextParent;
                        parentIndex = (ScholarNodePrimaryIndex) parentNode;
                    }
                }
            }
        }
    }

    public void addToSecondaryTree(CengPaper paper) {
        ScholarNodeSecondaryLeaf leafToInsert = findLeafSecondary(paper.journal());
        ArrayList<String> journalsOfLeaf = leafToInsert.getJournals();
        int max_capacity = 2 * ScholarNode.order + 1;
        int indexToInsertSec = -1;

        for (int i = 0; i < leafToInsert.journalCount(); i++) {
            int result = journalsOfLeaf.get(i).compareToIgnoreCase(paper.journal());
            if (result >= 0) {
                indexToInsertSec = i;
                break;
            }
        }

        if (indexToInsertSec == -1) {
            indexToInsertSec = leafToInsert.journalCount();
        }

        leafToInsert.addPaper(indexToInsertSec, paper);

        if (leafToInsert.journalCount() == max_capacity) {
            if (leafToInsert.getParent() == null) {
                ScholarNodeSecondaryIndex newRoot = new ScholarNodeSecondaryIndex(null);
                ScholarNodeSecondaryLeaf newNode = new ScholarNodeSecondaryLeaf(newRoot);

                for (int index = ScholarNode.order; index < leafToInsert.journalCount(); index++) {
                    newNode.getJournals().add(leafToInsert.journalAtIndex(index));
                    newNode.getPaperIdBucket().add(leafToInsert.papersAtIndex(index));
                }

                leafToInsert.getJournals().subList(ScholarNode.order, leafToInsert.getJournals().size()).clear();
                leafToInsert.getPaperIdBucket().subList(ScholarNode.order, leafToInsert.getPaperIdBucket().size()).clear();

                leafToInsert.setParent(newRoot);
                newRoot.addJournal(0, newNode.journalAtIndex(0));
                newRoot.addChild(0, leafToInsert);
                newRoot.addChild(1, newNode);

                secondaryRoot = newRoot;
            } else {
                ScholarNode parentNode = leafToInsert.getParent();
                ScholarNodeSecondaryIndex parentIndex = (ScholarNodeSecondaryIndex) parentNode;
                ScholarNodeSecondaryLeaf newNode = new ScholarNodeSecondaryLeaf(parentNode);

                for (int index = ScholarNode.order; index < leafToInsert.journalCount(); index++) {
                    newNode.getJournals().add(leafToInsert.journalAtIndex(index));
                    newNode.getPaperIdBucket().add(leafToInsert.papersAtIndex(index));
                }

                leafToInsert.getJournals().subList(ScholarNode.order, leafToInsert.getJournals().size()).clear();
                leafToInsert.getPaperIdBucket().subList(ScholarNode.order, leafToInsert.getPaperIdBucket().size()).clear();

                String journalToUp = newNode.journalAtIndex(0);
                boolean isSet = false;

                for (int i = 0; i < parentIndex.journalCount(); i++) {
                    int result = parentIndex.journalAtIndex(i).compareToIgnoreCase(journalToUp);
                    if (result >= 0) {
                        parentIndex.addJournal(i, journalToUp);
                        parentIndex.addChild(i + 1, newNode);
                        isSet = true;
                        break;
                    }
                }
                if (!isSet) {
                    parentIndex.addJournal(journalToUp);
                    parentIndex.addChild(newNode);
                }

                ScholarNode nextParent;
                ScholarNodeSecondaryIndex nextParentIndex;
                while (parentIndex.journalCount() == max_capacity) {
                    isSet = false;

                    nextParent = parentNode.getParent();
                    nextParentIndex = (ScholarNodeSecondaryIndex) nextParent;

                    if (parentNode == secondaryRoot) {
                        ScholarNodeSecondaryIndex newRoot = new ScholarNodeSecondaryIndex(null);
                        ScholarNodeSecondaryIndex newInternalNode = new ScholarNodeSecondaryIndex(newRoot);

                        for (int index = ScholarNode.order + 1, j = 0; index < parentIndex.journalCount(); index++, j++) {
                            newInternalNode.addJournal(j, parentIndex.journalAtIndex(index));
                            newInternalNode.addChild(j, parentIndex.getChildrenAt(index));
                            parentIndex.getChildrenAt(index).setParent(newInternalNode);
                        }
                        newInternalNode.addChild(newInternalNode.journalCount(), parentIndex.getChildrenAt(parentIndex.journalCount()));
                        parentIndex.getChildrenAt(parentIndex.journalCount()).setParent(newInternalNode);

                        journalToUp = parentIndex.journalAtIndex(ScholarNode.order);

                        parentIndex.getAllJournals().subList(ScholarNode.order, parentIndex.getAllJournals().size()).clear();
                        parentIndex.getAllChildren().subList(ScholarNode.order + 1, parentIndex.getAllChildren().size()).clear();

                        newRoot.addJournal(0, journalToUp);
                        newRoot.addChild(0, parentNode);
                        parentNode.setParent(newRoot);
                        newRoot.addChild(1, newInternalNode);
                        secondaryRoot = newRoot;
                        break;
                    } else {
                        ScholarNodeSecondaryIndex newInternalNode = new ScholarNodeSecondaryIndex(nextParent);

                        for (int index = ScholarNode.order + 1, j = 0; index < parentIndex.journalCount(); index++, j++) {
                            newInternalNode.addJournal(j, parentIndex.journalAtIndex(index));
                            newInternalNode.addChild(j, parentIndex.getChildrenAt(index));
                            parentIndex.getChildrenAt(index).setParent(newInternalNode);
                        }
                        newInternalNode.addChild(newInternalNode.journalCount(), parentIndex.getChildrenAt(parentIndex.journalCount()));
                        parentIndex.getChildrenAt(parentIndex.journalCount()).setParent(newInternalNode);

                        journalToUp = parentIndex.journalAtIndex(ScholarNode.order);

                        parentIndex.getAllJournals().subList(ScholarNode.order, parentIndex.getAllJournals().size()).clear();
                        parentIndex.getAllChildren().subList(ScholarNode.order + 1, parentIndex.getAllChildren().size()).clear();

                        for (int i = 0; i < nextParentIndex.journalCount(); i++) {
                            int result = nextParentIndex.journalAtIndex(i).compareToIgnoreCase(journalToUp);
                            if (result >= 0) {
                                nextParentIndex.addJournal(i, journalToUp);
                                nextParentIndex.addChild(i, parentNode);
                                nextParentIndex.setChild(i + 1, newInternalNode);
                                isSet = true;
                                break;
                            }
                        }
                        if (!isSet) {
                            nextParentIndex.addJournal(journalToUp);
                            nextParentIndex.addChild(newInternalNode);
                        }
                        parentNode = nextParent;
                        parentIndex = (ScholarNodeSecondaryIndex) nextParent;
                    }
                }
            }
        }
    }

    public ScholarNodePrimaryLeaf findLeafPrimary(Integer paperId) {
        ScholarNode node = primaryRoot;
        boolean found;

        while (node.getType() == ScholarNodeType.Internal) {
            ScholarNodePrimaryIndex indexNode = (ScholarNodePrimaryIndex) node;
            int paperIdCount = indexNode.paperIdCount();
            found = true;
            for (int i = 0; i < paperIdCount; i++) {
                if (indexNode.paperIdAtIndex(i) > paperId) {
                    node = indexNode.getChildrenAt(i);
                    found = false;
                    break;
                }
            }
            if (found) {
                node = indexNode.getChildrenAt(paperIdCount);
            }
        }

        return (ScholarNodePrimaryLeaf) node;
    }

    public ScholarNodeSecondaryLeaf findLeafSecondary(String journal) {
        ScholarNode node = secondaryRoot;
        boolean found;

        while (node.getType() == ScholarNodeType.Internal) {
            ScholarNodeSecondaryIndex indexNode = (ScholarNodeSecondaryIndex) node;
            int journalCount = indexNode.journalCount();
            found = true;

            for (int i = 0; i < journalCount; i++) {
                int result = indexNode.journalAtIndex(i).compareToIgnoreCase(journal);
                if (result > 0) {
                    node = indexNode.getChildrenAt(i);
                    found = false;
                    break;
                }
            }

            if (found) {
                node = indexNode.getChildrenAt(journalCount);
            }
        }

        return (ScholarNodeSecondaryLeaf) node;
    }

    public CengPaper searchPaperWithoutPrint(Integer paperId) {
        ScholarNode node = primaryRoot;
        boolean found;

        while (node.getType() == ScholarNodeType.Internal) {
            ScholarNodePrimaryIndex indexNode = (ScholarNodePrimaryIndex) node;
            int paperIdCount = indexNode.paperIdCount();
            found = true;
            for (int i = 0; i < paperIdCount; i++) {
                if (indexNode.paperIdAtIndex(i) > paperId) {
                    node = indexNode.getChildrenAt(i);
                    found = false;
                    break;
                }
            }
            if (found) {
                node = indexNode.getChildrenAt(paperIdCount);
            }
        }
        ScholarNodePrimaryLeaf leafNode = (ScholarNodePrimaryLeaf) node;
        int paperCount = leafNode.paperCount();
        for (int i = 0; i < paperCount; i++) {
            if (leafNode.paperIdAtIndex(i).equals(paperId)) {
                return leafNode.paperAtIndex(i);
            }
        }
        return null;
    }

    private void printPrimaryScholarHelper(ScholarNode node, int level) {
        if (node == null) {
            return;
        }

        String indentation = "\t".repeat(level);

        if (node.getType() == ScholarNodeType.Internal) {
            ScholarNodePrimaryIndex indexNode = (ScholarNodePrimaryIndex) node;
            ArrayList<ScholarNode> children = indexNode.getAllChildren();
            int paperIdCount = indexNode.paperIdCount();

            System.out.println(indentation + "<index>");
            for (int i = 0; i < paperIdCount; i++) {
                System.out.println(indentation + indexNode.paperIdAtIndex(i));
            }
            System.out.println(indentation + "</index>");

            for (ScholarNode child : children) {
                printPrimaryScholarHelper(child, level + 1);
            }
        } else if (node.getType() == ScholarNodeType.Leaf) {
            ScholarNodePrimaryLeaf leafNode = (ScholarNodePrimaryLeaf) node;
            int paperCount = leafNode.paperCount();

            System.out.println(indentation + "<data>");
            for (int i = 0; i < paperCount; i++) {
                System.out.print(indentation + "<record>");
                System.out.print(leafNode.paperAtIndex(i).fullName());
                System.out.print("</record>\n");
            }
            System.out.println(indentation + "</data>");
        }
    }

    private void printSecondaryScholarHelper(ScholarNode node, int level) {
        if (node == null) {
            return;
        }

        String indentation = "\t".repeat(level);

        if (node.getType() == ScholarNodeType.Internal) {
            ScholarNodeSecondaryIndex indexNode = (ScholarNodeSecondaryIndex) node;
            ArrayList<ScholarNode> children = indexNode.getAllChildren();
            int journalCount = indexNode.journalCount();

            System.out.println(indentation + "<index>");
            for (int i = 0; i < journalCount; i++) {
                System.out.println(indentation + indexNode.journalAtIndex(i));
            }
            System.out.println(indentation + "</index>");

            for (ScholarNode child : children) {
                printSecondaryScholarHelper(child, level + 1);
            }
        } else if (node.getType() == ScholarNodeType.Leaf) {
            ScholarNodeSecondaryLeaf leafNode = (ScholarNodeSecondaryLeaf) node;
            int journalCount = leafNode.journalCount();

            System.out.println(indentation + "<data>");
            for (int i = 0; i < journalCount; i++) {
                ArrayList<Integer> paperIdBucket = leafNode.papersAtIndex(i);
                System.out.println(indentation + leafNode.journalAtIndex(i));
                for (Integer paperId : paperIdBucket) {
                    CengPaper currentPaper = searchPaperWithoutPrint(paperId);
                    String recordIndentation = "\t".repeat(level + 1);
                    if (currentPaper.journal().equals(leafNode.journalAtIndex(i))) {
                        System.out.print(recordIndentation + "<record>");
                        System.out.print(currentPaper.paperId());
                        System.out.print("</record>\n");
                    }
                }
            }
            System.out.println(indentation + "</data>");
        }
    }
}


