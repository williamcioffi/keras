const burger = document.querySelector(".burger");
const navlinks = document.querySelector(".navlinks");
const links = document.querySelectorAll(".navlinks li");

burger.addEventListener("click", () => {
  navlinks.classList.toggle("open");
  
  links.forEach((link, index) => {
      if(link.style.animation) {
        link.style.animation = '';
      } else {
        link.style.animation = `navlinkfade 0.5s ease forwards ${index / 7 + 0.5}s`;
      }
    });
});
