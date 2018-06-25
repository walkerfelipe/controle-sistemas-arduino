from __future__ import print_function
import matplotlib
import numpy as np

matplotlib.use("TkAgg")

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation

import tkinter as tk
import ttk

x = np.linspace(0, 2*np.pi, 1024)


class TransientAnalysis(tk.Tk):

    pages = ((1, 'Switch to "-"', '-', '+', 'orange'),
             (-1, 'Switch to "+"', '+', '-', 'olive'))

    def __init__(self, *args, **kwargs):
        self._running_anim = None
        tk.Tk.__init__(self, *args, **kwargs)
        tk.Tk.wm_title(self, "Transient Analysis GUI: v1.0")

        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}

        for (direction, text, other_key, my_key, color) in self.pages:

            frame = MovingSinGraphPage(direction, text, other_key,
                                       my_key, color,
                                       container, self)

            self.frames[my_key] = frame

            frame.grid(row=0, column=0, sticky="nsew")

    def show_frame(self, cont):

        frame = self.frames[cont]
        frame.tkraise()
        frame.canvas.draw_idle()


class MovingSinGraphPage(tk.Frame):

    def __init__(self, move_dir, text, other_key, my_key,
                 color, parent, controller):
        self._sgn = np.sign(move_dir)

        tk.Frame.__init__(self, parent)

        button1 = ttk.Button(self, text=text,
                             command=(
                                 lambda: controller.show_frame(other_key)))
        button1.grid(row=1, column=0, pady=20, padx=10, sticky='w')

        # make mpl objects
        a = Figure(figsize=(4, 4))
        plot_a = a.add_subplot(111)
        # set up the axes limits and title
        plot_a.set_title(my_key)
        plot_a.set_xlim([0, 2*np.pi])
        plot_a.set_ylim([-1, 1])
        # make and stash the plot artist
        lna, = plot_a.plot([], [], color=color, lw=5)
        self._line = lna

        # make the canvas to integrate with Tk
        canvasA = FigureCanvasTkAgg(a, self)
        canvasA.show()
        canvasA.get_tk_widget().grid(
            row=1, column=1, pady=20, padx=10, sticky='nsew')

        # stash the canvas so that we can use it above to ensure a re-draw
        # when we switch to this page
        self.canvas = canvasA
        # create and save the animation
        self.anim = animation.FuncAnimation(a, self.update,
                                            interval=100)

    def update(self, i):
        self._line.set_xdata(x)
        self._line.set_ydata(np.sin(x + self._sgn * i * np.pi / 10))


app = TransientAnalysis()
app.geometry("800x600")

app.mainloop()