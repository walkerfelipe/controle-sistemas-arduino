import matplotlib
matplotlib.use('TkAgg')
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import Tkinter as tk  # python 2.7
import ttk            # python 2.7
import sys
import random

class Application(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self,master)
        self.createWidgets()

    def createWidgets(self):
        fig=plt.figure(figsize=(4,4))
        #ax=fig.add_axes([0.1,0.1,0.8,0.8],polar=True)
        ax=fig.add_subplot(111,polar=True)
        ax.set_title("Angulo da coisa")
        ax.set_rmax(2.0)
        ax.set_yticklabels([])
        ax.set_theta_zero_location("S")
        canvas=FigureCanvasTkAgg(fig,master=root)
        canvas.get_tk_widget().grid(row=1,column=1, pady=20, padx=10, sticky='nsew')
        canvas.show()


        ## fig 2
        fig2=plt.figure(figsize=(4,4))
        #ax=fig.add_axes([0.1,0.1,0.8,0.8],polar=True)
        ax2=fig2.add_subplot(111)
        ax2.set_title("Angulo da coisa")
        canvas2=FigureCanvasTkAgg(fig2,master=root)
        canvas2.get_tk_widget().grid(row=1,column=5, pady=20, padx=10, sticky='nsew')
        canvas2.show()
        self.plotbutton=tk.Button(master=root, text="plot", command=lambda: self.plot(canvas,ax))
        self.plotbutton.grid(row=0,column=0)
    def plot(self,canvas,ax):
        ax.clear()  # clear axes from previous plot
        ax.set_theta_zero_location("S")
        ax.set_yticklabels([])
        grau=random.randint(0,90)
        arr2 = plt.arrow(grau/180.*np.pi, 0.5, 0, 1, alpha = 0.5, width = 0.015,
        edgecolor = 'black', facecolor = 'green', lw = 2, zorder = 5) 
        canvas.draw()
        canvas.show()


root=tk.Tk()
root.geometry("1200x600")
app=Application(master=root)

app.mainloop()