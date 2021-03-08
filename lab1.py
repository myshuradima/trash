import psycopg2
import urllib.request
import py7zr
import os
from table import cteate_table, insert_string, ball_list

"""
conn = psycopg2.connect(
    host='localhost',
    port=5432,
    dbname='postgres',
    user='postgres',
    password='postgres'
)
cur = conn.cursor()
cur.execute(cteate_table)
cur.close()
conn.commit()
conn.close()"""
#way1 = 'https://zno.testportal.com.ua/yearstat/uploads/OpenDataZNO2019.7z'
#way2 = 'https://zno.testportal.com.ua/yearstat/uploads/OpenDataZNO2020.7z'
#urllib.request.urlretrieve(way1, '2019.7z')
#urllib.request.urlretrieve(way2, '2020.7z')

#with py7zr.SevenZipFile('2019.7z', 'r') as file:
#    file.extractall()
#with py7zr.SevenZipFile('2020.7z', 'r') as file:
#    file.extractall()


if not os.listdir(path="dir"):
    with open('Odata2019File.csv', encoding='cp1251') as file:
        a = file.readline()
        print(a)
        i = 0
        k = 0
        f = open('dir/partfile1_'+str(k)+'.csv', 'w')
        while a:
            if i < 5000:
                a = file.readline()
                f.write(a)
                i = i + 1
            else:
                f.close()
                i = 0
                k = k + 1
                f = open('dir/partfile1_' + str(k) + '.csv', 'w')
        f.close()
    with open('Odata2020File.csv', encoding='cp1251') as file:
        a = file.readline()
        print(a)
        i = 0
        k = 0
        f = open('dir/partfile2_'+str(k)+'.csv', 'w')
        while a:
            if i < 5000:
                a = file.readline()
                f.write(a)
                i = i + 1
            else:
                f.close()
                i = 0
                k = k + 1
                f = open('dir/partfile2_' + str(k) + '.csv', 'w')
        f.close()


print(len(os.listdir(path="dir")))


def func1(str_list):
    new_list = []
    for el in str_list:
        try:
            if el[0] == '"':
                el = el[1:-1]
                el = el.replace('""', '"')
                new_list.append(el)
            else:
                new_list.append(el)
        except:
            print(str_list)
    return new_list


conn = psycopg2.connect(
    host='localhost',
    port=5432,
    dbname='postgres',
    user='postgres',
    password='postgres'
)

counter1 = 0

for el in os.listdir(path="dir"):
    with open("dir/" + el, encoding="cp1251") as file:
        a = True
        while a and a != '':
            a = file.readline()
            a = a.rstrip("\n")
            a_list = a.split(';')
            if a_list != ['']:
                a_list = func1(a_list)
            for el in a_list:
                if len(el) > 250:
                    print(len(el))
            i = 0
            while i < len(a_list):
                if a_list[i] == "null":
                    a_list[i] = None
                elif i in ball_list:
                    a_list[i] = float(a_list[i].replace(',', '.'))
                i = i + 1

            if a_list != ['']:
                cur = conn.cursor()
                cur.execute(insert_string, a_list)
                cur.close()
    conn.commit()
    #os.remove("dir/" + el)
conn.close()

"""

conn = psycopg2.connect(
    host='localhost',
    port=5432,
    dbname='postgres',
    user='postgres',
    password='postgres'
)
cur = conn.cursor()
cur.execute(cteate_table)
cur.close()
conn.commit()
conn.close()
"""