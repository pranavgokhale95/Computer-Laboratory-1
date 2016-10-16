from __future__ import division
import math,os
from multiprocessing import Process,Queue
#probability for categorical attribute



def info(title):
    print title
    print 'module name:', __name__
    if hasattr(os, 'getppid'):  # only available on Unix
        print 'parent process:', os.getppid()
    print 'process id:', os.getpid()

#print gaussian_dis(30,18,6)
#print categorical_prob(20,[12,10,10,13,14,32,43],len([12,20,10,13,14,32,43]))

def readfile(filename):
	f = open(filename,"r")
	dictionary = {}
	dictionary['age']=[]
	dictionary['income']=[]
	dictionary['student']=[]
	dictionary['credit_rating'] = []
	dictionary['buys_computer'] = []
	for line in f:
		x = line.split(" ")
		dictionary['age'].append(x[0])
		dictionary['income'].append(x[1])
		dictionary['student'].append(x[2])
		dictionary['credit_rating'].append(x[3])
		dictionary['buys_computer'].append(x[4].rstrip())
	return dictionary



def getIncome(q):
    #income
    info('function getIncome')
    income_high_yes = 0
    income_high_no = 0
    income_low_no = 0
    income_low_yes = 0
    income_medium_yes = 0
    income_medium_no = 0
    len_yes=0
    len_no=0
    for x in xrange(tnor):
        if dicti['income'][x]=='high':
            if dicti['buys_computer'][x]=='yes':
                income_high_yes+=1
                len_yes+=1
            else:
                income_high_no+=1
                len_no+=1
        elif dicti['income'][x]=='low':
            if dicti['buys_computer'][x]=='yes':
                income_low_yes+=1
                len_yes+=1
            else:
                income_low_no+=1
                len_no+=1
        else:
            if dicti['buys_computer'][x]=='yes':
                income_medium_yes+=1
                len_yes+=1
            else:
                income_medium_no+=1
                len_no+=1
                
    income_high_yes_prob=income_high_yes/len_yes
    income_high_no_prob=income_high_no/len_no

    income_low_yes_prob=income_low_yes/len_yes
    income_low_no_prob=income_low_no/len_no

    income_medium_yes_prob = income_medium_yes/len_yes
    income_medium_no_prob = income_medium_no/len_no
    q.put([income_high_yes_prob,income_high_no_prob,income_low_yes_prob,income_low_no_prob,income_medium_yes_prob,income_medium_no_prob])


def getCreditRating(q):
    credit_fair_yes = 0
    credit_fair_no = 0
    credit_exc_yes = 0
    credit_exc_no = 0
    len_yes=0
    len_no=0
    for x in xrange(tnor):
        if dicti['credit_rating'][x]=='excellent':
            if dicti['buys_computer'][x]=='yes':
                    credit_exc_yes+=1
                    len_yes+=1
            else:
                    credit_exc_no+=1
                    len_no+=1    
        else:
            if dicti['buys_computer'][x]=='yes':
                    credit_fair_yes+=1
                    len_yes+=1
            else:
                    credit_fair_no+=1
                    len_no+=1    
    credit_fair_yes_prob = credit_fair_yes/len_yes
    credit_exec_yes_prob = credit_exc_yes/len_yes
    credit_fair_no_prob = credit_fair_no/len_no
    credit_exec_no_prob = credit_exc_no/len_no
    q.put([credit_fair_yes_prob,credit_fair_no_prob,credit_exec_yes_prob,credit_exec_no_prob])


def getStudentStatus(q):
    #student
    info('function getStudentStatus')
    studno_yes = 0
    studyes_yes = 0
    studno_no = 0
    studyes_no = 0
    len_yes=0
    len_no=0
    for x in xrange(tnor):
        if dicti['student'][x]=='no':
            if dicti['buys_computer'][x]=='yes':
                    studno_yes+=1
                    len_yes+=1
            else:
                    studno_no+=1
                    len_no+=1    
        else:
            if dicti['buys_computer'][x]=='yes':
                    studyes_yes+=1
                    len_yes+=1
            else:
                    studyes_no+=1
                    len_no+=1    
    studyes_yes_prob = studyes_yes/len_yes
    studyes_no_prob = studyes_no/len_no
    studno_yes_prob = studno_yes/len_yes
    studno_no_prob = studno_no/len_no
    q.put([studyes_yes_prob,studyes_no_prob,studno_yes_prob,studno_no_prob])

if __name__ == '__main__':
    dicti = readfile("data_nb.txt")
    print dicti

    #Total number of rows in the record
    tnor = len(dicti['buys_computer'])

    aprior_num_yes = 0
    for x in dicti['buys_computer']:
	    if x=='yes':
	    	aprior_num_yes+=1

    print len(dicti['buys_computer'])
    aprior_yes = aprior_num_yes/len(dicti['buys_computer'])
    #print aprior_yes
    aprior_no = (len(dicti['buys_computer'])-aprior_yes)/len(dicti['buys_computer'])

    yes_total_prob = 1
    no_total_prob = 1

    info('main line')
    q = Queue()
    p = []
    p1 = Process(target=getIncome, args=(q,))
    p2 = Process(target=getStudentStatus,args=(q,))
    p3 = Process(target=getCreditRating,args=(q,))
    p.append(p1)
    p.append(p2)
    p.append(p3)
    process_output = []
    for x in p:
        x.start()
        process_output.append(q.get())
    for x in p:
        x.join()
    income_high_yes_prob = process_output[0][0]
    income_high_no_prob = process_output[0][1]
    income_medium_yes_prob = process_output[0][2]
    income_medium_no_prob = process_output[0][3]
    income_low_yes_prob = process_output[0][4]
    income_low_no_prob = process_output[0][5]

    studyes_yes_prob = process_output[1][0]
    studyes_no_prob = process_output[1][1]
    studno_yes_prob = process_output[1][2]
    studno_no_prob = process_output[1][3]

    credit_fair_yes_prob = process_output[2][0] 
    credit_fair_no_prob = process_output[2][1]
    credit_exec_yes_prob = process_output[2][2]
    credit_exec_no_prob = process_output[2][3]


    income_x = raw_input("Enter the income:\n>")
    credit_x = raw_input("Enter the credit rating:\n>")
    stud_x = raw_input("Enter the student status:\n>")

    if income_x=='high':
        yes_total_prob*=income_high_yes_prob
        no_total_prob*=income_high_no_prob
    elif income_x=='medium':
        yes_total_prob*=income_medium_yes_prob
        no_total_prob*=income_medium_no_prob
    else:
        yes_total_prob*=income_low_yes_prob
        no_total_prob*=income_low_no_prob

    if credit_x=='fair':
        yes_total_prob*=credit_fair_yes_prob
        no_total_prob*=credit_fair_no_prob
    else:
        yes_total_prob*=credit_exec_yes_prob
        no_total_prob*=credit_exec_no_prob    

    if stud_x=='yes':
        yes_total_prob*=studyes_yes_prob
        no_total_prob*=studyes_no_prob
    else:
        yes_total_prob*=studno_yes_prob
        no_total_prob*=studno_no_prob



    print "No Probablility: "+str(no_total_prob)
    print "Yes Probability: "+str(yes_total_prob)
    if no_total_prob>yes_total_prob:
        print "NO"
    else:
        print "YES"    
