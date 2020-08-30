public class Programmers67256 {

    static Pos left;
    static Pos right;

    public String solution(int[] numbers, String hand) {
        String answer = "";
        left = new Pos(3, 0);
        right = new Pos(3, 2);

        for (int t : numbers) {
            if (t == 1 || t == 4 || t == 7) {
                left.move(t);
                answer += "L";
            } else if (t == 3 || t == 6 || t == 9) {
                right.move(t);
                answer += "R";
            } else {
                if (getCloseHand(t) > 0) { // left
                    left.move(t);
                    answer += "L";
                } else if (getCloseHand(t) < 0) { // right
                    right.move(t);
                    answer += "R";
                } else {// left == right
                    if (hand.equals("left")) {
                        left.move(t);
                        answer += "L";
                    } else {
                        right.move(t);
                        answer += "R";
                    }
                }
            }
        }
        return answer;
    }

    public static int getCloseHand(int num) {
        Pos dest = new Pos(num);
        int leftDist = Math.abs(left.getRow() - dest.getRow()) + Math.abs(left.getCol() - dest.getCol());
        int rightDist = Math.abs(right.getRow() - dest.getRow()) + Math.abs(right.getCol() - dest.getCol());
        return rightDist - leftDist;
    }

    public static class Pos {
        int row;
        int col;

        public Pos(int row, int col) {
            this.row = row;
            this.col = col;
        }

        public Pos(int dest) {
            move(dest);
        }

        public void move(int num) {
            if (num >= 1 && num <= 9) {
                int n = num - 1;
                this.row = n / 3;
                this.col = n % 3;
            } else {//0인경
                this.row = 3;
                this.col = 1;
            }
        }

        public int getRow() {
            return row;
        }

        public int getCol() {
            return col;
        }
    }
}
