SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `mqttsub` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;
USE `mqttsub` ;

-- -----------------------------------------------------
-- Table `mqttsub`.`machine`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mqttsub`.`machine` (
  `id` CHAR(10) NOT NULL,
  `clientid` VARCHAR(20) NULL,
  `mtype` CHAR(14) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mqttsub`.`newstat`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mqttsub`.`newstat` (
  `machine_id` CHAR(10) NOT NULL,
  `activetime` DATETIME NULL,
  `online` ENUM('Y','N') NULL,
  PRIMARY KEY (`machine_id`),
  CONSTRAINT `fk_newstat_machine`
    FOREIGN KEY (`machine_id`)
    REFERENCES `mqttsub`.`machine` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mqttsub`.`historystat`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mqttsub`.`historystat` (
  `machine_id` CHAR(10) NOT NULL,
  `activetime` DATETIME NOT NULL,
  `online` ENUM('Y','N') NULL,
  INDEX `fk_historystat_machine1_idx` (`machine_id` ASC),
  PRIMARY KEY (`machine_id`, `activetime`),
  CONSTRAINT `fk_historystat_machine1`
    FOREIGN KEY (`machine_id`)
    REFERENCES `mqttsub`.`machine` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mqttsub`.`historypos`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mqttsub`.`historypos` (
  `machine_id` CHAR(10) NOT NULL,
  `activetime` DATETIME NOT NULL,
  `lat` DOUBLE NULL,
  `lon` DOUBLE NULL,
  `radius` INT NULL,
  `address` VARCHAR(45) NULL,
  PRIMARY KEY (`machine_id`, `activetime`),
  CONSTRAINT `fk_historypos_machine1`
    FOREIGN KEY (`machine_id`)
    REFERENCES `mqttsub`.`machine` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mqttsub`.`newpos`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `mqttsub`.`newpos` (
  `machine_id` CHAR(10) NOT NULL,
  `lastpostdate` DATE NULL,
  `mcc` INT(10) UNSIGNED NULL DEFAULT NULL,
  `mnc` INT(10) UNSIGNED NULL DEFAULT NULL,
  `lac` INT(10) UNSIGNED NULL DEFAULT NULL,
  `ci` INT(10) UNSIGNED NULL DEFAULT NULL,
  `lat` DOUBLE NULL,
  `lon` DOUBLE NULL,
  `address` VARCHAR(45) NULL,
  PRIMARY KEY (`machine_id`),
  CONSTRAINT `fk_newpos_machine1`
    FOREIGN KEY (`machine_id`)
    REFERENCES `mqttsub`.`machine` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
