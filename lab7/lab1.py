from cassandra.cluster import Cluster
import json, glob, datetime

listoffiles = glob.glob("workshop_dataset1/*.json")
listofinputs = []
for file in listoffiles:
	curr_file = {}
	curr_file = json.load(open(file))	
	print file
	listofinputs.append(curr_file)


cluster = Cluster()
session = cluster.connect()

session.execute("CREATE KEYSPACE if not exists assignment1 WITH REPLICATION = {'class': 'SimpleStrategy', 'replication_factor' : 1 };")


# q3
session.execute("CREATE TABLE if not exists assignment1.ques3 (author_name TEXT, tweet_id TEXT, t_text TEXT, author_id TEXT, postdate DATE, usermention TEXT, location TEXT , PRIMARY KEY(usermention, location, tweet_id));")
print "Table 3 created"

for file in listofinputs:
	for key, val in file.items():
		strng = val['mentions']
		if strng:																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																
			for words in strng:
				if words or words != "":
					if val['location']:
						session.execute("""INSERT INTO assignment1.ques3 (author_name, tweet_id, t_text, author_id, postdate, usermention, location) VALUES (%s, %s, %s, %s,  %s, %s, %s)""",(val['author'], key, val['tweet_text'], val['author_id'], val['date'], words, val['location']))


# q9
session.execute("CREATE TABLE if not exists assignment1.ques9 (author_name TEXT, tweet_id TEXT, t_text TEXT, author_id TEXT, postdate DATE, hashtag_mention TEXT, PRIMARY KEY(hashtag_mention, postdate, tweet_id));")
print "Table 9 created"

for file in listofinputs:
	for key, val in file.items():
		strng = val['hashtags']
		if strng:																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																
			for words in strng:
				if words or words != "":
					strng2 = val['mentions']
					if strng2:																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																
						for words2 in strng2:
							if words2 or words2 != "":
								pairs = words + "-" + words2
								session.execute("""INSERT INTO assignment1.ques9 (author_name, tweet_id, t_text, author_id, postdate, hashtag_mention) VALUES (%s, %s, %s, %s, %s, %s)""",(val['author'], key, val['tweet_text'], val['author_id'], val['date'], pairs))



while(1):
	optionselect = int(raw_input("Enter a Query(3, 9, 1 to quit): "))
	if(optionselect == 3):
		fetch3 = raw_input('Enter a location: ')
		output = session.execute("""SELECT location, usermention, count(*) from assignment1.ques3 where location = '%s' group by usermention allow filtering;""" % fetch3)

		popularmention = {}
		for row in output:
			popularmention[row[0], row[1]] = row[2]
		toptrending = sorted(popularmention, key = popularmention.get, reverse = True)
		for row in toptrending:
			print row[0], row[1].encode('utf-8'), popularmention[row]
		print "Total Number of Rows: ", len(toptrending)
	elif(optionselect == 9):
		fetch9 = raw_input('Enter a date(YYYY-MM-DD): ')
		output = session.execute("""SELECT postdate, hashtag_mention, count(*) from assignment1.ques9 where postdate = '%s' group by hashtag_mention allow filtering;""" % fetch9)

		popularmention = {}
		for row in output:
			popularmention[row[0], row[1]] = row[2]
		toptrending = sorted(popularmention, key = popularmention.get, reverse = True)
		for row in toptrending:
			print row[0], row[1].encode('utf-8'), popularmention[row]
		print "Total Number of Rows: ", len(toptrending)
	elif(optionselect == 1):
		break



