class Solution {
    public int reverse(int x) {
        String numberString = String.valueOf(x);
        Boolean positive = true;
        if(x < 0) {
            numberString = String.valueOf(-x);
            positive = false;
        } 
        Integer lengthOfString = numberString.length();
        int newValue = 0;
        for(int i = (lengthOfString - 1); i >= 0 ; i--) {
            int currentNum = x / tenpow(lengthOfString - i - 1) % 10;
            if(positive) {
                if(newValue > Integer.MAX_VALUE / 10 || (newValue == Integer.MAX_VALUE / 10 && currentNum > Integer.MAX_VALUE % 10)) return 0;
            } else {
                if(newValue < Integer.MIN_VALUE / 10 || (newValue == Integer.MIN_VALUE /10  && currentNum < Integer.MIN_VALUE % 10)) return 0;
            }  
            newValue = newValue * 10 + currentNum;
          
        }
        return newValue;
    }
    public int tenpow(int i) {
        if(i == 0) return 1;
        int base = 10;
        i--;
        while(i > 0) {
            base *= 10;
            i--;
        }
        return base;
    }
}