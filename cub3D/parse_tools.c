/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psong <psong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 14:01:42 by psong             #+#    #+#             */
/*   Updated: 2021/05/31 15:55:14 by psong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_res(t_all *s)
{
	s->win.fov_h = deg2rad(FOV);
	s->win.a_p_pixel = s->win.fov_h / (s->win.x - 1);
	s->win.fov_v = (s->win.fov_h * (double)s->win.y / (double)s->win.x);
	s->win.fovh_2 = s->win.fov_h / 2.0;
	s->win.p_p_angle = (s->win.x - 1) / s->win.fov_h;
	return (0);
}

int		ft_colors(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);
	(*i)++;
	r = ft_atoi(line, i);
	if (line[*i] != ',')
		return (-6);
	(*i)++;
	g = ft_atoi(line, i);
	if (line[*i] != ',')
		return (-6);
	(*i)++;
	b = ft_atoi(line, i);
	ft_spaceskip(line, i);
	if (!(line[*i] == '\0' && (0 <= r && r <= 255)
				&& (0 <= g && g <= 255) && (0 <= b && b <= 255)))
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

void	ft_pos(t_all *s, int i, int j, double th)
{
	char	c;

	while (++i < s->map.x)
	{
		while (++j < s->map.y)
		{
			c = s->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				s->pos.x = (double)i + 0.5;
				s->pos.y = (double)j + 0.5;
				if (c == 'E')
					th = 180;
				else if (c == 'N')
					th = 270;
				else if (c == 'W')
					th = 0;
				else if (c == 'S')
					th = 90;
				s->pos.th = deg2rad(th);
				s->err.p++;
			}
		}
		j = -1;
	}
}

void	map_extend(t_all *s, int a, int b, int i)
{
	char **tmp;
	char **tmp2;

	tmp = malloc(sizeof(char *) * (s->map.x + 1));
	while (++a < s->map.x)
	{
		tmp[a] = malloc(sizeof(char) * (s->map.l + 1));
		while (s->map.tab[a][++b] != '\0')
			tmp[a][b] = s->map.tab[a][b];
		while (b < s->map.l)
		{
			tmp[a][b] = ' ';
			b++;
		}
		tmp[a][b] = '\0';
		b = -1;
	}
	tmp[a] = NULL;
	tmp2 = s->map.tab;
	s->map.tab = tmp;
	while (++i < s->map.x + 1)
		free(tmp2[i]);
	free(tmp2);
}
