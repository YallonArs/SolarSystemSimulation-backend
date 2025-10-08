# Transforming coordinates from Keplerian to Cartesian

Некоторые обозначения:

$a$ — большая полуось\
$e$ — эксцентриситет\
$\omega$ — аргумент перицентра\
$p = a(1-e^2)$ — фокальный параметр

$A = \sqrt\frac{GM}{p}$

$r = \frac{p}{1 - e \cos\varphi}$ - уравнение эллипса в полярных координатах

<!-- Полная скорость на эллипсе (aka "интеграл энергии"):
$$v = \sqrt{\frac{2}{}}$$ -->

## Перевод координат

Формулы для радиальной и трансверсальной скоростей известны из небесной механики:

$$
\begin{align*}
 v_r &= Ae\sin\varphi\\
 v_\tau &= A(1+e\cos\varphi)
\end{align*}
$$

Запишем вектор скорости в осях, связанных с движущимся телом, так, чтобы ось $X$ была направлена вдоль вектора движения:

$$
\overrightarrow{v} = \overrightarrow{v_r} + \overrightarrow{v_\tau}
= A\begin{bmatrix}
e\sin\varphi \\
1 + e\cos\varphi
\end{bmatrix}.
$$

Введём новую систему координат. Ось $X$ направлена вдоль линии апсид в сторону от фокуса (=от центрального тела) в сторону перицентра.

Для перехода в новую систему координат необходимо повернуть вектор скорости на угол $\varphi$.

$$
\begin{aligned}
\overrightarrow{v_{x'}}
&=
\begin{bmatrix}
 \cos\varphi & -\sin\varphi\\
 \sin\varphi & \cos\varphi\\
\end{bmatrix}\cdot
A\begin{bmatrix}
e\sin\varphi \\
1 + e\cos\varphi
\end{bmatrix}\cdot

\\
&=A\begin{bmatrix}
e\sin\varphi \cos\varphi - \sin\varphi - e\sin\varphi \cos\varphi\\
e\sin^2\varphi + \cos\varphi + e\cos^2\varphi
\end{bmatrix}
\end{aligned}
$$
$$
\boxed{
\overrightarrow{v_{x'}}
=A\begin{bmatrix}
 -\sin\varphi\\
 \cos\varphi + e
\end{bmatrix}
}
$$

Теперь повернём эту систему координат на угол $\omega$:

$$
\begin{align*}
\overrightarrow{v_x}
&=\begin{bmatrix}
 \cos\omega & -\sin\omega\\
 \sin\omega & \cos\omega\\
\end{bmatrix}\cdot
A\begin{bmatrix}
 -\sin\varphi\\
 \cos\varphi + e
\end{bmatrix} =\\
&=A\begin{bmatrix}
	-\sin\varphi \cos\omega - (\cos\varphi+e)\sin\omega\\
	-\sin\varphi \sin\omega + (\cos\varphi+e)\cos\omega
\end{bmatrix}
\end{align*}
$$

$$
\boxed{
\overrightarrow{v_x} = A\begin{bmatrix}
	-\left(\sin(\varphi+\omega) + e\sin\omega\right)\\
	\cos(\varphi+\omega) + e\cos\omega
\end{bmatrix}
}
$$
