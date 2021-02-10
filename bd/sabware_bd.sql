-- phpMyAdmin SQL Dump
-- version 4.9.0.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 02-02-2021 a las 05:04:26
-- Versión del servidor: 10.4.6-MariaDB
-- Versión de PHP: 7.3.9

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `sabware_bd`
--
DROP DATABASE IF EXISTS sabware_bd;
CREATE DATABASE sabware_bd;
USE sabware_bd;

DELIMITER $$
--
-- Procedimientos
--
CREATE DEFINER=`root`@`localhost` PROCEDURE `AgregarUsuarioCajero` (`Idusuario` INT, `Nombre` VARCHAR(45), `contrasenia` VARCHAR(45), `A_M` VARCHAR(45), `A_P` VARCHAR(45), `Direccion` VARCHAR(45), `Telefono` VARCHAR(45))  BEGIN
INSERT INTO USUARIO(idUsuario,contrasenia,nombre,a_materno,a_paterno,direccion,telefono)
VALUES(Idusuario,contrasenia,Nombre,A_M,A_P,Direccion,Telefono);
INSERT INTO cajero(idCajero,idUsuario)
VALUES((SELECT MAX(idUsuario) FROM USUARIO),(SELECT MAX(idUsuario) FROM USUARIO));
END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `AgregarUsuarioEncargado` (`Idusuario` INT, `Nombre` VARCHAR(45), `contrasenia` VARCHAR(45), `A_M` VARCHAR(45), `A_P` VARCHAR(45), `Direccion` VARCHAR(45), `Telefono` VARCHAR(45))  BEGIN
INSERT INTO USUARIO(idUsuario,contrasenia,nombre,a_materno,a_paterno,direccion,telefono)
VALUES(Idusuario,contrasenia,Nombre,A_M,A_P,Direccion,Telefono);
INSERT INTO encargado(idEncargado,idUsuario)
VALUES((SELECT MAX(idUsuario) FROM USUARIO),(SELECT MAX(idUsuario) FROM USUARIO));
END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `AgregarUsuarioGerente` (`Idusuario` INT, `Nombre` VARCHAR(45), `contrasenia` VARCHAR(45), `A_M` VARCHAR(45), `A_P` VARCHAR(45), `Direccion` VARCHAR(45), `Telefono` VARCHAR(45))  BEGIN
INSERT INTO USUARIO(idUsuario,contrasenia,nombre,a_materno,a_paterno,direccion,telefono)
VALUES(Idusuario,contrasenia,Nombre,A_M,A_P,Direccion,Telefono);
INSERT INTO gerente(idGerente,idUsuario)
VALUES((SELECT MAX(idUsuario) FROM USUARIO),(SELECT MAX(idUsuario) FROM USUARIO));
END$$

CREATE DEFINER=`root`@`localhost` PROCEDURE `AgregarUsuarioMesero` (`Idusuario` INT, `Nombre` VARCHAR(45), `contrasenia` VARCHAR(45), `A_M` VARCHAR(45), `A_P` VARCHAR(45), `Direccion` VARCHAR(45), `Telefono` VARCHAR(45))  BEGIN
INSERT INTO USUARIO(idUsuario,contrasenia,nombre,a_materno,a_paterno,direccion,telefono)
VALUES(Idusuario,contrasenia,Nombre,A_M,A_P,Direccion,Telefono);
INSERT INTO Mesero(idMesero,idUsuario)
VALUES((SELECT MAX(idUsuario) FROM USUARIO),(SELECT MAX(idUsuario) FROM USUARIO));
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

INSERT INTO `categoria_menu` VALUES (1, "Entradas"), (2, "Plato fuerte"), (3, "Postre"), (4, "Bebidas");

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

INSERT INTO `elemento_menu` VALUES (1, "Sopa de verdura", "Sopa de verduras de jitomate", 20, 1),
(2, "Sopa de pasta", "Sopa de pasta de jitomate", 20, 1),
(3, "Spaghetti rojo", "Spaghetti seco en salsa de jitomate", 30, 1),
(4, "Consome de pollo", "Consome de caldo de pollo con verduras", 20, 1),
(5, "Milanesa", "Milanesa de puerco acompañada con ensalada y papas fritas", 35, 2),
(6, "Mole verde", "Mole verde de carne de puerco", 35, 2),
(7, "Mole poblano", "Mole poblano picoso con pollo", 40, 2),
(8, "Mosaico", "Gelatina de mosaico con crema", 20, 3),
(9, "Fresas con crema", "Fresas con cream acida y azucar", 15, 3),
(10, "Flan", "Rebanada de flan napolitano", 20, 3),
(11, "Vaso de agua", "Vaso de agua de sabor del dia", 10, 4),
(12, "Litro de agua", "Litro de agua de sabor del dia", 25, 4),
(13, "Refresco lata", "Refresco de lata 355 ml", 15, 4),
(14, "Refresco envase", "Refresco de envase 600 ml", 20, 4);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `encargado`
--

CREATE TABLE `encargado` (
  `idEncargado` int(11) NOT NULL,
  `idUsuario` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `encargado`
--

INSERT INTO `encargado` (`idEncargado`, `idUsuario`) VALUES
(1, 1);

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
  `idGerente` int(11) NOT NULL,
  `idUsuario` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `gerente`
--

INSERT INTO `gerente` (`idGerente`, `idUsuario`) VALUES
(1, 2);

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
  `idUsuario` int(11) NOT NULL,
  `idZona` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `mesero`
--

INSERT INTO `mesero` (`idMesero`, `idUsuario`, `idZona`) VALUES
(1, 3, 2),
(202, 202, NULL);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `orden`
--

CREATE TABLE `orden` (
  `idOrden` int(11) NOT NULL,
  `fecha` date NOT NULL,
  `total` float NOT NULL,
  `idMesero` int(11) NOT NULL,
  `idCajero` int(11) NOT NULL,
  `idMesa` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

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
  ADD KEY `fk_idUsuario` (`idUsuario`);

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
  ADD PRIMARY KEY (`idEncargado`) USING BTREE,
  ADD KEY `fk_idUsuario` (`idUsuario`);

--
-- Indices de la tabla `gerente`
--
ALTER TABLE `gerente`
  ADD PRIMARY KEY (`idGerente`),
  ADD KEY `fk_idUsuario` (`idUsuario`);

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
  ADD KEY `fk_idUsuario` (`idUsuario`),
  ADD KEY `idZona` (`idZona`);

--
-- Indices de la tabla `orden`
--
ALTER TABLE `orden`
  ADD PRIMARY KEY (`idOrden`),
  ADD KEY `fk_idMesero` (`idMesero`),
  ADD KEY `fk_idCajero` (`idCajero`),
  ADD KEY `fk_idMesa` (`idMesa`);

--
-- Indices de la tabla `usuario`
--
ALTER TABLE `usuario`
  ADD PRIMARY KEY (`idUsuario`);

--
-- Indices de la tabla `zona`
--
ALTER TABLE `zona`
  ADD PRIMARY KEY (`idZona`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `cajero`
--
ALTER TABLE `cajero`
  MODIFY `idCajero` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `gerente`
--
ALTER TABLE `gerente`
  MODIFY `idGerente` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `cajero`
--
ALTER TABLE `cajero`
  ADD CONSTRAINT `cajero_ibfk_1` FOREIGN KEY (`idUsuario`) REFERENCES `usuario` (`idUsuario`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `detalleorden`
--
ALTER TABLE `detalleorden`
  ADD CONSTRAINT `detalleorden_ibfk_1` FOREIGN KEY (`idOrden`) REFERENCES `orden` (`idOrden`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `detalleorden_ibfk_2` FOREIGN KEY (`idPlatillo`) REFERENCES `elemento_menu` (`idPlatillo`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `elemento_menu`
--
ALTER TABLE `elemento_menu`
  ADD CONSTRAINT `elemento_menu_ibfk_1` FOREIGN KEY (`idCategoria`) REFERENCES `categoria_menu` (`idCategoria`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Filtros para la tabla `encargado`
--
ALTER TABLE `encargado`
  ADD CONSTRAINT `encargado_ibfk_1` FOREIGN KEY (`idUsuario`) REFERENCES `usuario` (`idUsuario`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `gerente`
--
ALTER TABLE `gerente`
  ADD CONSTRAINT `gerente_ibfk_1` FOREIGN KEY (`idUsuario`) REFERENCES `usuario` (`idUsuario`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `mesa`
--
ALTER TABLE `mesa`
  ADD CONSTRAINT `mesa_ibfk_1` FOREIGN KEY (`idZona`) REFERENCES `zona` (`idZona`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `mesero`
--
ALTER TABLE `mesero`
  ADD CONSTRAINT `mesero_ibfk_1` FOREIGN KEY (`idUsuario`) REFERENCES `usuario` (`idUsuario`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `mesero_ibfk_2` FOREIGN KEY (`idZona`) REFERENCES `zona` (`idZona`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Filtros para la tabla `orden`
--
ALTER TABLE `orden`
  ADD CONSTRAINT `orden_ibfk_1` FOREIGN KEY (`idMesero`) REFERENCES `mesero` (`idMesero`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `orden_ibfk_2` FOREIGN KEY (`idCajero`) REFERENCES `cajero` (`idCajero`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `orden_ibfk_3` FOREIGN KEY (`idMesa`) REFERENCES `mesa` (`idMesa`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
