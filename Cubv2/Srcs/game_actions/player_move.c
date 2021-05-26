/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellon <ebellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:11:21 by ebellon           #+#    #+#             */
/*   Updated: 2021/05/26 16:12:38 by ebellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../Headers/cub3d.h"

double			modulo(double x, double y)
{
	x -= y * floor(x / y);
	if (x >= 0.)
		return (x);
	else
		return (x+y);
}

static void		move_player3(t_game *game)
{
	double oldDirX;
	double oldPlaneX;
	if (game->data.key.r_arr)
	{
		game->player.alpha = modulo((game->player.alpha + ROTATE), (2 * PI));
		oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(ROTATE) - game->player.dirY * sin(ROTATE);
		game->player.dirY = oldDirX * sin(ROTATE) + game->player.dirY * cos(ROTATE);
		oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(ROTATE) - game->player.planeY * sin(ROTATE);
		game->player.planeY = oldPlaneX * sin(ROTATE) + game->player.planeY * cos(ROTATE);
	}
	if (game->data.key.l_arr)
	{
		game->player.alpha = modulo((game->player.alpha - ROTATE), (2 * PI));
		oldDirX = game->player.dirX;
		game->player.dirX = game->player.dirX * cos(-ROTATE) - game->player.dirY * sin(-ROTATE);
		game->player.dirY = oldDirX * sin(-ROTATE) + game->player.dirY * cos(-ROTATE);
		oldPlaneX = game->player.planeX;
		game->player.planeX = game->player.planeX * cos(-ROTATE) - game->player.planeY * sin(-ROTATE);
		game->player.planeY = oldPlaneX * sin(-ROTATE) + game->player.planeY * cos(-ROTATE);
	}
	if (game->data.map[(int)game->player.y][(int)game->player.x] != '2' &&
		game->data.map[(int)game->player.y][(int)game->player.x] != '3' &&
		game->data.map[(int)game->player.y][(int)game->player.x] != '4')
		game->data.map[(int)game->player.y][(int)game->player.x] = '*';
}

static void		move_player2(t_game *game)
{
	if (game->data.key.a)
	{
		if (game->data.map[(int)floor(game->player.y - ((sin(game->player.alpha + (PI/2))) * SPEED))][(int)floor(game->player.x)] != '1' &&
			!(game->data.map[(int)floor(game->player.y - ((sin(game->player.alpha + (PI/2))) * SPEED))][(int)floor(game->player.x)] == '4' && game->trip == 0))
			game->player.y -= ((sin(game->player.alpha + (PI/2))) * SPEED);
		if (game->data.map[(int)floor(game->player.y)][(int)floor(game->player.x - ((cos(game->player.alpha + (PI/2))) * SPEED))] != '1' &&
			!(game->data.map[(int)floor(game->player.y)][(int)floor(game->player.x - ((cos(game->player.alpha + (PI/2))) * SPEED))] == '4' && game->trip == 0))
			game->player.x -= ((cos(game->player.alpha + (PI/2))) * SPEED);
	}
	if (game->data.key.d)
	{
		if (game->data.map[(int)floor(game->player.y + ((sin(game->player.alpha + (PI/2))) * SPEED))][(int)floor(game->player.x)] != '1' &&
			!(game->data.map[(int)floor(game->player.y + ((sin(game->player.alpha + (PI/2))) * SPEED))][(int)floor(game->player.x)] == '4' && game->trip == 0))
			game->player.y += ((sin(game->player.alpha + (PI/2))) * SPEED);
		if (game->data.map[(int)floor(game->player.y)][(int)floor(game->player.x + ((cos(game->player.alpha + (PI/2))) * SPEED))] != '1' &&
			!(game->data.map[(int)floor(game->player.y)][(int)floor(game->player.x + ((cos(game->player.alpha + (PI/2))) * SPEED))] == '4' && game->trip == 0))
			game->player.x += ((cos(game->player.alpha + (PI/2))) * SPEED);
	}
	move_player3(game);
}

void			move_player(t_game *game)
{
	if (game->data.map[(int)game->player.y][(int)game->player.x] == '2' && game->trip == 0)
		game->trip = 5;
	else if (game->data.map[(int)game->player.y][(int)game->player.x] == '3')
		game->trip = 0;
	else if (game->data.map[(int)game->player.y][(int)game->player.x] != '1' &&
		game->data.map[(int)game->player.y][(int)game->player.x] != '4' &&
		game->data.map[(int)game->player.y][(int)game->player.x] != '2')
		game->data.map[(int)game->player.y][(int)game->player.x] = ' ';
	if (game->data.key.w)
	{
		if (game->data.map[(int)floor(game->player.y + ((sin(game->player.alpha)) * SPEED))][(int)floor(game->player.x)] != '1' &&
			!(game->data.map[(int)floor(game->player.y + ((sin(game->player.alpha)) * SPEED))][(int)floor(game->player.x)] == '4' && game->trip == 0))
			game->player.y += ((sin(game->player.alpha)) * SPEED);
		if (game->data.map[(int)floor(game->player.y)][(int)floor(game->player.x + (cos(game->player.alpha)) * SPEED)] != '1' &&
			!(game->data.map[(int)floor(game->player.y)][(int)floor(game->player.x + (cos(game->player.alpha)) * SPEED)] == '4' && game->trip == 0))
			game->player.x += ((cos(game->player.alpha)) * SPEED);
	}
	if (game->data.key.s)
	{
		if (game->data.map[(int)floor(game->player.y - ((sin(game->player.alpha)) * SPEED))][(int)floor(game->player.x)] != '1' &&
			!(game->data.map[(int)floor(game->player.y - ((sin(game->player.alpha)) * SPEED))][(int)floor(game->player.x)] == '4' && game->trip == 0))
			game->player.y -= ((sin(game->player.alpha)) * SPEED);
		if (game->data.map[(int)floor(game->player.y)][(int)floor(game->player.x - ((cos(game->player.alpha)) * SPEED))] != '1' &&
			!(game->data.map[(int)floor(game->player.y)][(int)floor(game->player.x - ((cos(game->player.alpha)) * SPEED))] == '4' && game->trip == 0))
			game->player.x -= ((cos(game->player.alpha)) * SPEED);
	}
	move_player2(game);
}