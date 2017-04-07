from __future__ import print_function

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm
import matplotlib.colors as mplcolors
import matplotlib.ticker



#Function to add ticks
def addticks(ax,newLocs,newLabels,pos='x',replace=True):
    # Draw to get ticks
    plt.draw()
    
    # Get existing ticks
    if pos=='x':
        locs   = ax.get_xticks().tolist()
        labels = [x.get_text() for x in ax.get_xticklabels()]
    elif pos =='y':
        locs = ax.get_yticks().tolist()
        labels=[x.get_text() for x in ax.get_yticklabels()]
    else:
        print("WRONG pos. Use 'x' or 'y'")
        return
    
    if replace is True:
        Dticks=dict(zip(newLocs,newLabels))
    else:
        # Build dictionary of ticks
        Dticks=dict(zip(locs,labels))
        
        # Add/Replace new ticks
        for Loc,Lab in zip(newLocs,newLabels):
            Dticks[Loc]=Lab

    # Get back tick lists
    locs=list(Dticks.keys())
    labels=list(Dticks.values())

    # Generate new ticks
    if pos=='x':
        ax.set_xticks(locs)
        ax.set_xticklabels(labels)
    elif pos =='y':
        ax.set_yticks(locs)
        ax.set_yticklabels(labels)



data = np.loadtxt('graphene.dat')

kx = data[:,0]
ky = data[:,1]
E1 = data[:,2]
E2 = data[:,3]

s = int(E1.size/3)
E1_MG = E1[0:s]
E2_MG = E2[0:s]
E1_GK = E1[s:2*s]
E2_GK = E2[s:2*s]
E1_KM = E1[2*s:]
E2_KM = E2[2*s:]
x = np.linspace(0,s,s)

fig, ax1 = plt.subplots(figsize=[12.,8.])

fig.suptitle(r'$E(k)$',fontsize=20)
ax1.grid(True)
ax1.set_xlim([0.,300.])
ax1.xaxis.set_major_locator(plt.NullLocator())
ax1.set_ylabel('$E-E_F$ [eV]',fontsize=15)

cNorm  = mplcolors.Normalize(vmin=0, vmax=data.shape[1])
scalarMap = cm.ScalarMappable(norm=cNorm, cmap=cm.jet)

ax1.plot(x,E1_MG,color='blue')
ax1.plot(x,E2_MG,color='red')
ax1.plot(x+s-2,E1_GK,color='blue')
ax1.plot(x+s-2,E2_GK,color='red')
ax1.plot(x+2*s-2,E1_KM,color='blue')
ax1.plot(x+2*s-2,E2_KM,color='red')
ax1.axvline(s-1,color='k',linestyle='--')
ax1.axvline(2*s-2,color='k',linestyle='--')
ax1.axvline(3*s-3,color='k',linestyle='--')

ax1.text(  5.0,12.0,r'M',fontsize=20)
ax1.text( 90.0,12.0,r'$\Gamma$',fontsize=20)
ax1.text(190.0,12.0,r'K',fontsize=20)
ax1.text(290.0,12.0,r'M',fontsize=20)

# customize axis description
stepsize = 1./6.

ax2 = ax1.twiny()
ax2.set_xlabel('$k_y$',fontsize=15)
ax2.xaxis.set_label_coords(1.05, 1.025)
start, end = ax2.get_xlim()
labels = map(lambda x : '{:.2f}'.format(np.abs(x)),[kx[0],kx[50],kx[100],kx[151],kx[201],kx[252],kx[302]])
#ax2.xaxis.set_major_locator(plt.NullLocator())
#ax2.xaxis.set_ticks(np.arange(start, end, stepsize),labels)

addticks(ax2,np.arange(start, end, stepsize),labels,pos='x')

print(np.arange(start, end, stepsize))
print([item.get_text() for item in ax2.get_xticklabels()])


ax3 = ax2.twiny()
ax3.set_xlabel('$k_x$',fontsize=15)
ax3.xaxis.set_label_coords(1.05, -0.025)
start, end = ax3.get_xlim()
#ax3.xaxis.set_ticks(np.arange(start, end, stepsize))
#ax3.xaxis.set_major_formatter(matplotlib.ticker.FormatStrFormatter('%0.1f'))
labels = map(lambda x : '{:.2f}'.format(np.abs(x)),[ky[0],ky[50],ky[100],ky[151],ky[201],ky[252],ky[302]])


addticks(ax3,np.arange(start, end, stepsize),labels,pos='x')

ax1.legend()
plt.savefig('graphene.png')
plt.show()