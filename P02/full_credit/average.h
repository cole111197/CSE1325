class Average{
  private:
    double _sum;
    int _values;
  public:
    Average();
    friend ostream operator<<(ostream& ost, Average& average);
    friend istream operator>>(istream& ist, Average& average);
    Average& operator+=(double value);
}
