# ByunCargo: a video analysis program for microswimmers

Hi all,

I developed a video analysis program to track the trajectories of (catalytic) microswimmers [https://en.wikipedia.org/wiki/Microswimmer].
My video analysis program for microswimmers is written in Microsoft Visual C++ and runs on Windows.
My program *automatically* analyzes a video file and *mathematically* calculates two kinds of trajectories of microswimmers:
- **Position** using the geometric center (centroid) [https://en.wikipedia.org/wiki/Centroid]
- **Orientation** using the moment of inertia tensor [https://en.wikipedia.org/wiki/Moment_of_inertia#Inertia_tensor]

Using the translational and rotational trajectories of microswimmers above, one can *accurately* find the following properties of microparticles suspended in a fluid:
- Self-propulsion speed
- Advection (flow) speed
- Translational diffusion coefficients along the principal axes
- Rotational diffusion coefficient 

I used my video analysis program in the following papers:
- **Young-Moo Byun**, Paul E. Lammert, Yiying Hong, Ayusman Sen, and Vincent H. Crespi, Distinguishing advective and powered motion in self-propelled colloids, *J. Phys.: Condens. Matter* **29**, 445101 (2017) [https://doi.org/10.1088/1361-648X/aa88f1] **NOTE: This paper is selected for the JPCM highlights of 2017.** [https://iopscience.iop.org/journal/0953-8984/page/Highlights-2017] WARNING: In this paper, the experiment part, which I didn't write, is false, but my theory, Mathematics, statistics, programming, algorithm, data analysis, and visualization parts are true.
- Amir Nourhani, **Young-Moo Byun**, Paul E. Lammert, Ali Borhan, and Vincent H. Crespi, Nanomotor mechanisms and motive force distributions from nanorotor trajectories, *Phys. Rev. E* **88**, 062317 (2013) [https://doi.org/10.1103/PhysRevE.88.062317]
- Yang Wang, Shih-to Fei, **Young-Moo Byun**, Paul E. Lammert, Vincent H. Crespi, Ayusman Sen, Thomas E. Mallouk, Dynamic Interactions between Fast Microscale Rotors, *J. Am. Chem. Soc.* **131**, 9926 (2009) [https://doi.org/10.1021/ja904827j]

Please let me know if you have any questions.

Thanks,

Young-Moo Byun

Last updated on 2025/05/11
