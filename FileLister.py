import sys
sys.stdout = open('script_Filelister','w')

def getVarFromFile(filename):
    import imp
    f = open(filename)
    global data
    data = imp.load_source('data', '', f)
    f.close()
getVarFromFile('InputDetails.dat')



for a in range(0,len(data.list_mc_sig)):
    
    print "ls",data.path+data.list_mc_sig[a],">Sig_Files_%i.dat"%(a) 
    print '\n'
    print 'sed -i s/eos// Sig_Files_%i.dat'%(a)
    print 'sed -i s/uscms// Sig_Files_%i.dat'%(a)
    print '\n'

for a in range(0,len(data.list_mc_bkg)):
    print "ls",data.path+data.list_mc_bkg[a],">Bkg_Files_%i.dat"%(a)
    print 'sed -i s/eos// Bkg_Files_%i.dat'%(a)
    print 'sed -i s/uscms// Bkg_Files_%i.dat'%(a)
    print '\n'


