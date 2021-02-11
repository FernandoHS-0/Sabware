-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost
-- Tiempo de generación: 11-02-2021 a las 05:30:28
-- Versión del servidor: 10.4.6-MariaDB
-- Versión de PHP: 7.3.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `sabware_bd`
--

DROP DATABASE IF EXISTS `sabware_bd`;
CREATE DATABASE `sabware_bd`;

USE `sabware_bd`;

DELIMITER $$
--
-- Procedimientos
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `AgregarUsuarioCajero` (`Idusuario` INT, `Nombre` VARCHAR(45), `contrasenia` VARCHAR(45), `A_M` VARCHAR(45), `A_P` VARCHAR(45), `Direccion` VARCHAR(45), `Telefono` VARCHAR(45))  BEGIN
INSERT INTO USUARIO(idUsuario,contrasenia,nombre,a_materno,a_paterno,direccion,telefono)
VALUES(Idusuario,contrasenia,Nombre,A_M,A_P,Direccion,Telefono);
INSERT INTO cajero(idCajero)
VALUES((SELECT MAX(idUsuario) FROM USUARIO));
END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `AgregarUsuarioEncargado` (`Idusuario` INT, `Nombre` VARCHAR(45), `contrasenia` VARCHAR(45), `A_M` VARCHAR(45), `A_P` VARCHAR(45), `Direccion` VARCHAR(45), `Telefono` VARCHAR(45))  BEGIN
INSERT INTO USUARIO(idUsuario,contrasenia,nombre,a_materno,a_paterno,direccion,telefono)
VALUES(Idusuario,contrasenia,Nombre,A_M,A_P,Direccion,Telefono);
INSERT INTO encargado(idEncargado)
VALUES((SELECT MAX(idUsuario) FROM USUARIO));
END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `AgregarUsuarioGerente` (`Idusuario` INT, `Nombre` VARCHAR(45), `contrasenia` VARCHAR(45), `A_M` VARCHAR(45), `A_P` VARCHAR(45), `Direccion` VARCHAR(45), `Telefono` VARCHAR(45))  BEGIN
INSERT INTO USUARIO(idUsuario,contrasenia,nombre,a_materno,a_paterno,direccion,telefono)
VALUES(Idusuario,contrasenia,Nombre,A_M,A_P,Direccion,Telefono);
INSERT INTO gerente(idGerente)
VALUES((SELECT MAX(idUsuario) FROM USUARIO));
END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `AgregarUsuarioMesero` (`Idusuario` INT, `Nombre` VARCHAR(45), `contrasenia` VARCHAR(45), `A_M` VARCHAR(45), `A_P` VARCHAR(45), `Direccion` VARCHAR(45), `Telefono` VARCHAR(45))  BEGIN
INSERT INTO USUARIO(idUsuario,contrasenia,nombre,a_materno,a_paterno,direccion,telefono)
VALUES(Idusuario,contrasenia,Nombre,A_M,A_P,Direccion,Telefono);
INSERT INTO Mesero(idMesero)
VALUES((SELECT MAX(idUsuario) FROM USUARIO));
END$$

DELIMITER ;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cajero`
--

CREATE TABLE `cajero` (
  `idCajero` int(11) NOT NULL,
  `idUsuario` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `categoria_menu`
--

CREATE TABLE `categoria_menu` (
  `idCategoria` int(11) NOT NULL,
  `nombre_categoria` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `categoria_menu`
--

INSERT INTO `categoria_menu` (`idCategoria`, `nombre_categoria`) VALUES
(1, 'Entradas'),
(2, 'Plato fuerte'),
(3, 'Postre'),
(4, 'Bebidas');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `detalleorden`
--

CREATE TABLE `detalleorden` (
  `cantidad` int(11) NOT NULL,
  `subtotal` float NOT NULL,
  `idOrden` int(11) NOT NULL,
  `idPlatillo` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `detalleorden`
--

INSERT INTO `detalleorden` (`cantidad`, `subtotal`, `idOrden`, `idPlatillo`) VALUES
(9, 230, 1, 3),
(1, 20, 1, 4),
(3, 60, 1, 2),
(2, 40, 1, 10),
(1, 20, 1, 14),
(5, 100, 1, 1),
(3, 60, 1, 2),
(1, 20, 2, 1),
(1, 30, 2, 3),
(1, 20, 2, 4);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `elemento_menu`
--

CREATE TABLE `elemento_menu` (
  `idPlatillo` int(11) NOT NULL,
  `nombre_platillo` varchar(45) NOT NULL,
  `descripcion` text NOT NULL,
  `precio` double NOT NULL,
  `idCategoria` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `elemento_menu`
--

INSERT INTO `elemento_menu` (`idPlatillo`, `nombre_platillo`, `descripcion`, `precio`, `idCategoria`) VALUES
(1, 'Sopa de verdura', 'Sopa de verduras de jitomate', 20, 1),
(2, 'Sopa de pasta', 'Sopa de pasta de jitomate', 20, 1),
(3, 'Spaghetti rojo', 'Spaghetti seco en salsa de jitomate', 30, 1),
(4, 'Consome de pollo', 'Consome de caldo de pollo con verduras', 20, 1),
(5, 'Milanesa', 'Milanesa de puerco acompañada con ensalada y papas fritas', 35, 2),
(6, 'Mole verde', 'Mole verde de carne de puerco', 35, 2),
(7, 'Mole poblano', 'Mole poblano picoso con pollo', 40, 2),
(8, 'Mosaico', 'Gelatina de mosaico con crema', 20, 3),
(9, 'Fresas con crema', 'Fresas con cream acida y azucar', 15, 3),
(10, 'Flan', 'Rebanada de flan napolitano', 20, 3),
(11, 'Vaso de agua', 'Vaso de agua de sabor del dia', 10, 4),
(12, 'Litro de agua', 'Litro de agua de sabor del dia', 25, 4),
(13, 'Refresco lata', 'Refresco de lata 355 ml', 15, 4),
(14, 'Refresco envase', 'Refresco de envase 600 ml', 20, 4);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `encargado`
--

CREATE TABLE `encargado` (
  `idEncargado` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `encargado`
--

INSERT INTO `encargado` (`idEncargado`) VALUES
(1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `fotos`
--

CREATE TABLE `fotos` (
  `Id_foto` int(11) NOT NULL,
  `imgen` longblob DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `gerente`
--

CREATE TABLE `gerente` (
  `idGerente` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `gerente`
--

INSERT INTO `gerente` (`idGerente`) VALUES
(2);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `inventario`
--

CREATE TABLE `inventario` (
  `idProducto` int(11) NOT NULL,
  `nombre_pr` varchar(45) NOT NULL,
  `descripcion_pr` text NOT NULL,
  `cantidad` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `mesa`
--

CREATE TABLE `mesa` (
  `idMesa` int(11) NOT NULL,
  `estado` varchar(45) NOT NULL,
  `idZona` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `mesa`
--

INSERT INTO `mesa` (`idMesa`, `estado`, `idZona`) VALUES
(1, 'libre', 1),
(3, 'libre', 2),
(5, 'libre', 3),
(6, 'libre', 2),
(8, 'libre', 3),
(9, 'libre', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `mesero`
--

CREATE TABLE `mesero` (
  `idMesero` int(11) NOT NULL,
  `idZona` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `mesero`
--

INSERT INTO `mesero` (`idMesero`, `idZona`) VALUES
(3, 2),
(202, 2);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `orden`
--

CREATE TABLE `orden` (
  `idOrden` int(11) NOT NULL,
  `fecha` date NOT NULL,
  `total` float DEFAULT NULL,
  `idMesero` int(11) NOT NULL,
  `idCajero` int(11) DEFAULT NULL,
  `idMesa` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `orden`
--

INSERT INTO `orden` (`idOrden`, `fecha`, `total`, `idMesero`, `idCajero`, `idMesa`) VALUES
(1, '2021-02-10', NULL, 202, NULL, 1),
(2, '2021-02-10', NULL, 3, NULL, 2),
(3, '2021-02-10', NULL, 3, NULL, 1),
(4, '2021-02-10', NULL, 3, NULL, 1),
(5, '2021-02-10', NULL, 3, NULL, 1),
(6, '2021-02-10', NULL, 3, NULL, 1),
(7, '2021-02-10', NULL, 3, NULL, 1),
(8, '2021-02-10', NULL, 3, NULL, 1),
(9, '2021-02-10', NULL, 3, NULL, 1),
(10, '2021-02-10', NULL, 3, NULL, 1),
(11, '2021-02-10', NULL, 3, NULL, 1),
(12, '2021-02-10', NULL, 3, NULL, 1),
(13, '2021-02-10', NULL, 3, NULL, 1),
(14, '2021-02-10', NULL, 3, NULL, 1),
(15, '2021-02-10', NULL, 3, NULL, 1),
(16, '2021-02-10', NULL, 3, NULL, 1),
(17, '2021-02-10', NULL, 3, NULL, 1),
(18, '2021-02-10', NULL, 3, NULL, 1),
(19, '2021-02-10', NULL, 3, NULL, 1),
(20, '2021-02-10', NULL, 3, NULL, 1),
(21, '2021-02-10', NULL, 3, NULL, 1),
(22, '2021-02-10', NULL, 3, NULL, 1),
(23, '2021-02-10', NULL, 3, NULL, 1),
(24, '2021-02-10', NULL, 3, NULL, 1),
(25, '2021-02-10', NULL, 3, NULL, 1),
(26, '2021-02-10', NULL, 3, NULL, 1),
(27, '2021-02-10', NULL, 3, NULL, 2);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `usuario`
--

CREATE TABLE `usuario` (
  `idUsuario` int(11) NOT NULL,
  `contrasenia` varchar(45) NOT NULL,
  `nombre` varchar(45) NOT NULL,
  `a_materno` varchar(45) NOT NULL,
  `a_paterno` varchar(45) NOT NULL,
  `direccion` varchar(45) NOT NULL,
  `telefono` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `usuario`
--

INSERT INTO `usuario` (`idUsuario`, `contrasenia`, `nombre`, `a_materno`, `a_paterno`, `direccion`, `telefono`) VALUES
(1, 'encargado1', 'Fernando', 'Hernandez', 'Sanchez', 'Av Madero 32', '2345674789'),
(2, 'gerente1', 'Alberto', 'Martinez', 'Gonzalez', 'Ignacio Zaragoza 23', '2345213456'),
(3, 'mesero1', 'Saul', 'Garcia', 'Sanchez', 'Polimeros 21', '2458975614'),
(4, 'cajero1', 'Stephane', 'Perez', 'Perez', 'Indios verdes 9', '2484918619'),
(202, '123', 'Saul', 'Garcia', 'Mendez', 'Enrique Segoviano', '23833851065');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `zona`
--

CREATE TABLE `zona` (
  `idZona` int(11) NOT NULL,
  `capacidad` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `zona`
--

INSERT INTO `zona` (`idZona`, `capacidad`) VALUES
(1, 5),
(2, 5),
(3, 5);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `cajero`
--
ALTER TABLE `cajero`
  ADD PRIMARY KEY (`idCajero`),
  ADD KEY `fk_idUsuario` (`idCajero`);

--
-- Indices de la tabla `categoria_menu`
--
ALTER TABLE `categoria_menu`
  ADD PRIMARY KEY (`idCategoria`);

--
-- Indices de la tabla `detalleorden`
--
ALTER TABLE `detalleorden`
  ADD KEY `fk_idOrden` (`idOrden`),
  ADD KEY `fk_idPlatillo` (`idPlatillo`);

--
-- Indices de la tabla `elemento_menu`
--
ALTER TABLE `elemento_menu`
  ADD PRIMARY KEY (`idPlatillo`),
  ADD KEY `fk_idCategoria` (`idCategoria`);

--
-- Indices de la tabla `encargado`
--
ALTER TABLE `encargado`
  ADD PRIMARY KEY (`idEncargado`),
  ADD KEY `fk_idUsuario` (`idEncargado`);

--
-- Indices de la tabla `gerente`
--
ALTER TABLE `gerente`
  ADD PRIMARY KEY (`idGerente`),
  ADD KEY `fk_idUsuario` (`idGerente`);

--
-- Indices de la tabla `inventario`
--
ALTER TABLE `inventario`
  ADD PRIMARY KEY (`idProducto`);

--
-- Indices de la tabla `mesa`
--
ALTER TABLE `mesa`
  ADD PRIMARY KEY (`idMesa`),
  ADD KEY `idZona` (`idZona`);

--
-- Indices de la tabla `mesero`
--
ALTER TABLE `mesero`
  ADD PRIMARY KEY (`idMesero`),
  ADD KEY `fk_idUsuario` (`idMesero`),
  ADD KEY `idZona` (`idZona`);

--
-- Indices de la tabla `orden`
--
ALTER TABLE `orden`
  ADD PRIMARY KEY (`idOrden`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `orden`
--
ALTER TABLE `orden`
  MODIFY `idOrden` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=28;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
