from timeseries import dtwdistance
lista = [1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0]
listb = [1.0,6.0,2.0,3.0,0.0,9.0,4.0,3.0,6.0,3.0]
print dtwdistance(lista,listb)

steady = [0.0,0.0,0.0,0.0,0.0,0.0,0.0]
trendup1 = [0.0,0.0,0.0,2.0,4.0,8.0,16.0]
trendup2 = [0.0,0.0,0.0,2.0,4.0,8.0,16.0]
trenddown1 =[16.0,8.0,4.0,2.0,0.0,0.0,0.0]
str_trend = ["hi", "heelo", "bye"]
short_trend =[16.0,8.0,5.0,3.0]

print dtwdistance(trendup1,trendup2)
print dtwdistance(trendup1,steady)
print dtwdistance(steady,trendup1)
print dtwdistance(trendup1,trenddown1)
print dtwdistance(trenddown1,trendup1)
print dtwdistance(short_trend,trenddown1)
print dtwdistance(trenddown1,short_trend)
try:
   dtwdistance(trenddown1,str_trend)
except Exception, e:
    print e
try:
   dtwdistance(trenddown1,1)
except Exception, e:
    print e

