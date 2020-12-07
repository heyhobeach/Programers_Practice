#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <conio.h>
using namespace std;

class Point {
    int x, y;

public:
    Point(int pos_x, int pos_y) {
        x = pos_x;
        y = pos_y;
    }

    Point(const Point & p1):
        x(p1.x),
        y(p1.y){}

    //Point(Point &point):x(point.x),y(point.y){}

    int get_x() { 
        return x; 
    }
    int get_y() { 
        return y; 
    }
};

class Geometry {
    // �� 100 ���� �����ϴ� �迭.
    Point* point_array[100];
    int pos_x, pos_y,array_num;
public:
    Geometry(Point** point_list) {
        for (unsigned int i = 0; i < 3; i++) {
            point_array[i] =new Point((*point_list[i]).get_x(), (*point_list[i]).get_y());//����Ʈ Ŭ������ �ִ� get_x�� �����ϴ°ű⶧���� '->'�����ϰų� (*).���� �����ؾ���
            array_num = i;
        }
    }
    Geometry() :array_num(0) {};

    void AddPoint(const Point& p1) {//const�� Ŭ���� ��ü ������ ���� ������ ���Ұ� �б� �����̶�� �� const Point& point �б⸸ �ض�
            array_num++;
            point_array[array_num] = new Point(p1);// �����ڰ� ���� ���� ���Ҽ��� �־ �������°Ű���
   
    }
    ~Geometry() {
        for (unsigned int i = 0; i < array_num; i++) {
            delete point_array[i];
        }
    }

    // ��� ���� ���� �Ÿ��� ����ϴ� �Լ� �Դϴ�.
    void PrintDistance() {
        for (unsigned int i = 0; i <array_num; i++) {
            for (unsigned int j = i+1; j < array_num; j++) {
                cout << "x"<<i<<" -  x"<<j<<" "  << point_array[i]->get_x() << " -  " << point_array[j]->get_x();
                
                    
                    
                cout << "=" << sqrt(pow((point_array[i]->get_x() - point_array[j]->get_x()), 2)) << endl;
                
                    cout<< "y" << i << " -  y" << j <<" " <<point_array[i]->get_y() << " -  " << point_array[j]->get_y()
                        <<"="<< sqrt(pow((point_array[i]->get_y() - point_array[j]->get_y()), 2))<<endl;
            }
        }
    }

    // ��� ������ �մ� ������ ���� ������ ���� ������ִ� �Լ� �Դϴ�.
    // ���������� ������ �� ���� �մ� ������ �������� f(x,y) = ax+by+c = 0
    // �̶�� �� �� ������ �ٸ� �� �� (x1, y1) �� (x2, y2) �� f(x,y)=0 �� ��������
    // ���� �ٸ� �κп� ���� ������ f(x1, y1) * f(x2, y2) <= 0 �̸� �˴ϴ�.
    void PrintNumMeets() {
        cout << "�������";
        int m;
        int** cross_list;
        int line_count = 0;
        int b = 0;
        int b2 = 0;
        for (unsigned int i = 0; i < array_num; i++) {
            for (unsigned int j = i + 1; j < array_num; j++) {
                
                m= (point_array[j]->get_y() - point_array[i]->get_y() / (point_array[j]->get_x() - point_array[i]->get_x()));
                b = (point_array[i]->get_y() - point_array[i]->get_x() * m);//������ ������
                b2= (point_array[j]->get_y() - point_array[j]->get_x() * m);//������ ������
                if (b * b2 <= 0) {
                    line_count += 1;
                }
       
            }
        }
        cout << "������" << line_count;
    }
};

int main()
{
    int a, b;
    unsigned int num = 3;
    Point p1(3,4), p2(8,6);
    Point** point_list;
    point_list = new Point * [3];
    for (unsigned int i = 0; i < num; i++) {
        cout << "���� ��ǥ �Է�";
        cin >> a >> b;
        point_list[i] = new Point(a, b);
        cout << point_list[i] << endl;
    }
    Geometry geometry1(point_list);
    geometry1.AddPoint(p1);
    geometry1.AddPoint(p2);
    geometry1.PrintDistance();
    geometry1.PrintNumMeets();


    //delete point_list;
    for (unsigned int i = 0; i < num; i++) {
        delete point_list[i];
    }delete point_list;

    return 0;
}
