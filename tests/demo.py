from linear_model import linear_model as LM
lm = LM()
x = [0,1,2,3,4,5,6,7,8,9]
y = [5,10,25,30,40,50,65,70,80,90]

lm.LinearRegression(x, y)
print("done with linear_regression()")
print("lm.a:",lm.a)
print("lm.b:",lm.b)
print("score:",lm.score)

import matplotlib.pyplot as plt
plt.plot(x, y, 'bo')
plt.plot([0,x[len(x)-1]], [lm.a,x[len(x)-1]*lm.b], 'r--')
plt.legend(['count',' y = '+str(lm.a)+'x+ '+str(lm.b)+', R2='+str(lm.score)], loc='upper left')
plt.show()


x = [1,2,3,4,5,6,7]
trendup = [0.0, 0.0, 0.0, 2.0, 4.0,8.0,16.0]
trendflat = [16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0]
trenddown =[16.0,8.0,4.0,2.0,0.0,0.0,0.0]
week1_count = [0.0, 0.0, 0.0, 4.0, 8.0,16.0,32.0]
week2_count = [32.0,16.0,8.0,4.0, 0.0, 0.0,0.0 ]
week3_count = [0.0, 0.0, 1.0, 2.0, 5.0,6.0,6.0]

plt.plot(x, trendup,'k--')
plt.plot(x, trenddown, 'r--')
plt.plot(x, week1_count,'ko')
plt.plot(x, week2_count, 'm^')
plt.plot(x, week3_count, 'c^')
plt.legend(['trendup', 'trenddown', 'week1 count', 'week1 count','week3 count'], loc='center left',bbox_to_anchor=(1, 0.5))
plt.show()

#from expletics.timeseries import dtw
from expletics.dtw import dtw
up = dtw(week1_count,trendup)
down = dtw(week1_count,trenddown)
trending = down/up > 1.0
print(trending)

up = dtw(week2_count,trendup)
down = dtw(week2_count,trenddown)
trending = down/up > 1.0
print(trending)

up = dtw(week3_count,trendup)
down = dtw(week3_count,trenddown)
trending = down/up > 1.0
print(trending)



#perceptron = LM()
#lm.perceptron()