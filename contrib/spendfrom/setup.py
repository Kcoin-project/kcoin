from distutils.core import setup
setup(name='KBCspendfrom',
      version='1.0',
      description='Command-line utility for kcoin "coin control"',
      author='Gavin Andresen',
      author_email='gavin@kcoinfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
