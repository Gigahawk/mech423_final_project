% Use separate page for title
\LoadClass[titlepage]{article}

% math is kinda important
\usepackage{amsmath}
\usepackage{amssymb}
\usepackage{dsfont}
\newcommand\numberthis{\addtocounter{\equation}{1}\tag{\theequation}}
\usepackage{graphicx}
% \textsubscript
%\usepackage{fixltx2e}

% 1 inch margins
\usepackage{geometry}
\geometry{margin=1.0in}

% Fancy enumerate options
\usepackage{enumerate}

% Better references
\usepackage[hidelinks]{hyperref}
\usepackage[noabbrev]{cleveref}

% Customize titlepage
\usepackage{titling}

% Add subtitle command
\newcommand{\subtitle}[1]{%
  \posttitle{%
    \par\end{center}
    \begin{center}\large#1\end{center}
    \vskip0.5em}%
}

% Add spacing before author block
\preauthor{
    \vspace{5em}
    \begin{center}
    \large \lineskip 0.5em%
    \begin{tabular}[t]{c}
}

% Add spacing before date block
\predate{
    \vspace{5em}
    \begin{center}\large 
}

% Add spacing between paragraphs, keep indenting behavior
\edef\restoreparindent{\parindent=\the\parindent\relax}
\usepackage{parskip}
\restoreparindent

% Allow svg figures
\usepackage{svg}

% Allow floats to be unfloated
\usepackage{float}
\usepackage{graphicx}
% Have units
\usepackage[per-mode=symbol]{siunitx}

% Inches are nice I guess
\DeclareSIUnit\inch{in}

% Slugs are too I guess
\DeclareSIUnit\slug{slug}

% Idk a different Tau character makes sense to me
\newcommand{\Tau}{\mathrm{T}}

\usepackage{caption}

%More space in fractions
\newcommand{\ddfrac}[2]{{\displaystyle\frac{\displaystyle #1}{\displaystyle #2}}}

%highlighting stuff is good sometimes
\usepackage{soul}

%Crossing out in math is pretty
\usepackage{calc}
\usepackage[makeroom]{cancel}

%better tables
\usepackage{booktabs} 
\usepackage{multicol}
\usepackage{multirow}

%This is like programming block stuffs
\usepackage{listings}
\usepackage{color}
\lstset{frame=tb,
  language=Matlab, %%Change the language here
  aboveskip=3mm,
  belowskip=3mm,
  showstringspaces=false,
  columns=flexible,
  basicstyle={\small\ttfamily},
  numbers=left,
  numberstyle=\tiny\color{gray},
  keywordstyle=\color{blue},
  commentstyle=\color{dkgreen},
  stringstyle=\color{mauve},
  breaklines=true,
  breakatwhitespace=true,
  tabsize=3
}
\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{mauve}{rgb}{0.58,0,0.82}
\newcommand{\laplace}[0]{\mathcal{L}}
\usepackage{rotating}
\usepackage[bottom]{footmisc}%Force footnote to actually be at bottom
\usepackage{adjustbox} %For scaling tables
%\usepackage[demo]{graphicx}
\newcommand{\eig}[0]{\text{eig}}
\usepackage{subcaption}
\setlength{\parindent}{0pt}
\usepackage{tabularx}