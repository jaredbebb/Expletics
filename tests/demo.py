from linear_model import linear_model as LM
lm = LM()
print"lm:", lm
x = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
y = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
print x,y
lm.LinearRegression(x, y)
print "done with linear_regression()"
print"lm.a",lm.a,"."
print "score:",lm.score
print x,y