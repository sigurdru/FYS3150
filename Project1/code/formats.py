class Table:
  def __init__(self, data):
    self.data = data
    self.endline = r'    \\ \hline'

  def latex(self, filename='print'):
    """Print or save to file a latex formatted table."""
    try:
      data = self.data
    except (TypeError, AttributeError):
      print('No table was written or printed')
      print('Initialize Table instance with table data first.')
      return
    width = len(data[0])
    out = self.texHeader(width)
    for line in data:
      out.append(' & '.join(line) + self.endline)
    out += self.texFooter()
    if filename == 'print':
      for line in out:
        print(line)
    else:
      with open(filename, 'w') as outfile:
        for line in out:
          outfile.write(line + '\n')

  def texHeader(self, width): 
    out = ['\\begin{table}  %[p] % Uncomment to put table in Appendix',
           '\\begin{adjustbox}{width=1\\textwidth}',
           '\\begin{{{:s}}}{{||c | {:s}c||}}'.format('tabular', 'c | '*(width-2)),
           '\\hline']
    return out

  def texFooter(self):
    out = ['\\end{tabular}',
           '\\end{adjustbox}',
           '\\caption{}',
           '\\label{}',
           '\\end{table}']
    return out

  def write(self, filename='print'):
    """Print or save to file a good old-fashioned table."""
    try:
      data = self.data
    except (TypeError, AttributeError):
      print('No table was written or printed.')
      print('Initialize Table instance with table data first.')
      return
    import numpy as np
    bins = np.zeros(len(data[0]))
    for i in range(len(bins)):
      column = [data[j][i] for j in range(len(data))]
      bins[i] = len(max(column, key=len))+4
    out = []
    for i in range(len(data)):
      line = ''
      for j in range(len(data[i])):
        line += '|{:{align}{width}}'.format(data[i][j], align='^', width=str(int(bins[j])))
      line += '|'
      out.append(line)
    out.insert(0, '-'*len(line))
    out.insert(2, '|' + '-'*(len(line)-2) + '|')
    out.append('-'*len(line))
    if filename == 'print':
      for line in out:
        print(line)
    else:
      with open(filename, 'w') as outfile:
        for line in out:
          outfile.write(line + '\n')

class Matrix(Table):
  def __init__(self, data):
    self.data = data
    self.endline = r'  \\'
  def texHeader(self, width):
    out = [r'\begin{equation}{}',
           r'\bm NAME = \begin{bmatrix}']
    return out

  def texFooter(self):
    out = [r'\end{bmatrix}',
           r'\end{equation}']
    return out

if __name__ == '__main__':
    import numpy as np
    A = np.random.uniform(size=(5, 4))
    data = [['{:.4f}'.format(num) for num in row] for row in A]

    mat = Matrix(data)
    mat.latex(filename='print') 

    print()
    data.insert(0, ['Vec {}'.format(i+1) for i in range(4)])
    mat = Matrix(data)
    mat.write(filename='print')
    
    print()
    data[0] = ['Col {}'.format(i+1) for i in range(4)]
    tab = Table(data)
    tab.latex(filename='print')
    print()
    tab.write(filename='print')
