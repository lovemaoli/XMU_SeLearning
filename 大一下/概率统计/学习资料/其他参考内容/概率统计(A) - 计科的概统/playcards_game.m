%%%%%%%%%%%%%
%
%%%%%%%%%%%%%
clc;
clear all;

%%%%%%%%%%%%%% 最小牌型
for n = 1:13
    for m = 1:4
        desk( (n-1)*4+m ) = n;
    end
end

iteration = 1e4;
count = 0;
for it = 1:iteration
    
    ini = randperm(52,5);
    hand = desk(ini);
    card = zeros(1,13);
    hand_tmp = unique(hand);
 
    card(hand_tmp) = ones(size(hand_tmp));
    if sum(card)==5
        count = count +1;
    end
end
prob = count/iteration
prob_th = nchoosek(13,5)*4^5/nchoosek(52,5)
        

%  有一对特定的，如一对K
desk(1:4) = ones(1,4);
desk(5:52) = zeros(1,48);
count = 0;
for it = 1:iteration
    
    ini = randperm(52,5);
    hand = desk(ini);

    if sum(hand)==2
        count = count +1;
    end
end
probk = count/iteration
probk_th = nchoosek(4,2)*nchoosek(48,3)/nchoosek(52,5)

%  恰有一对
for n = 1:13
    for m = 1:4
        desk( (n-1)*4+m ) = n;
    end
end

%%%%%%%%%%%%%%%%%%%%%%
count = 0;
for it = 1:iteration
    
    ini = randperm(52,5);
    hand = desk(ini);
    card = zeros(1,13);
    hand_tmp = unique(hand);
 
    card(hand_tmp) = ones(size(hand_tmp));
    if sum(card)==4
        count = count +1;
    end
end
probc = count/iteration
probc_th = 13*6*nchoosek(12,3)*4^3/nchoosek(52,5)


%%%%%%%%%%%%%% 各堆各有一张A %%%%%%%%

desk(1:4) = ones(1,4);
desk(5:52) = zeros(1,48);

iteration = 1e4;
count = 0;
for it = 1:iteration
    
    ini = randperm(52);
    hand = desk(ini);
    
    flg = 0;
    for k = 1:4
        tmp = sum( hand( (k-1)*13+1:k*13 ) );
        
        if tmp == 1
            flg = flg +1;
        end
    end
    if flg == 4
        count = count + 1;
    end
end
probA = count/iteration
probA_th = ( factorial(48)/factorial(12)^4*factorial(4) )/( factorial(52)/factorial(13)^4 )


% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% %  ???????
% for n = 1:13
%     for m = 1:4
%         desk( (n-1)*4+m ) = n;
%     end
% end
% 
% iteration = 1e4;
% count = 0;
% for it = 1:iteration
%     
%     ini = randperm(52,5);
%     hand = desk(ini);
%     [hand_tmp,tmp] = sort(hand);
%  
%    
%     if hand_tmp(1)==hand_tmp(2) && hand_tmp(2)==hand_tmp(3) && hand_tmp(2)~=hand_tmp(3)
%         count = count +1;
%     end
%     if hand_tmp(2)==hand_tmp(3) && hand_tmp(3)==hand_tmp(4)
%         count = count +1;
%     end
%     
%     if hand_tmp(1)~=hand_tmp(2) && hand_tmp(3)==hand_tmp(4) && hand_tmp(4)==hand_tmp(5)
%         count = count +1;
%     end
% end
% probthree = count/iteration
% 
% 
% 
% %  ???????
% for n = 1:13
%     for m = 1:4
%         desk( (n-1)*4+m ) = n;
%     end
% end
% 
% %%%%%%%%%%%%%%%%%%%%%%
% count = 0;
% iteration = 1e7;
% for it = 1:iteration
%     
%     ini = randperm(52,5);
%     hand = desk(ini);
%     hand1 = unique(hand);
% 
%     if ( hand1(1)==hand1(2) ) && ( hand1(2)==hand1(3) ) 
%         &&  ( hand1(4)==hand1(5) )
%         count = count +1;
%     end
%     if ( hand1(1)==hand1(2) ) && ( hand1(3)==hand1(4) ) 
%         &&  ( hand1(4)==hand1(5) )
%         count = count +1;
%     end
% 
% end
% probt = count/iteration
% 
% %  ???????
% for n = 1:13
%     for m = 1:4
%         desk( (n-1)*4+m ) = n;
%     end
% end
% 
% %%%%%%%%%%%%%%%%%%%%%%
% count = 0;
% iteration = 1e7;
% for it = 1:iteration
%     
%     ini = randperm(52,5);
%     hand = desk(ini);
%     [hand1,id] = sort(hand);
%      %hand1 = [1 2 3 4 5];
%     if ( hand1(1)+1==hand1(2) && hand1(2)+1==hand1(3) && hand1(3)+1==hand1(4) && hand1(4)+1==hand1(5) )
%         count = count +1;
%     end
%    if(length(hand_tmp)==2)
%        count = count +1;
%    end
% end
% probs = count/iteration
% 
% 
% %  ???????
% desk = 1:52;
% 
% 
% %%%%%%%%%%%%%%%%%%%%%%
% count = 0;
% iteration = 1e7;
% for it = 1:iteration
%     
%     ini = randperm(52,5);
%     hand = desk(ini);
%     [hand1,id] = sort(hand);
%     if ( hand1(1)+1==hand1(2) && hand1(2)+1==hand1(3) && hand1(3)+1==hand1(4) && hand1(4)+1==hand1(5) )
%         count = count +1;
%     end
%    if(length(hand_tmp)==2)
%        count = count +1;
%    end
% end
% probs = count/iteration
