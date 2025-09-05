// Menu mobile
const hamburger = document.querySelector('.hamburger');
const navLinks = document.querySelector('.nav-links');
const links = document.querySelectorAll('.nav-links li');

// Gestion du clic sur le menu hamburger
if (hamburger) {
  hamburger.addEventListener('click', () => {
    // Animation du bouton
    hamburger.classList.toggle('active');
    
    // Affichage du menu
    if (navLinks) navLinks.classList.toggle('active');
    
    // Animation des liens
    links.forEach((link, index) => {
      if (link.style.animation) {
        link.style.animation = '';
      } else {
        link.style.animation = `navLinkFade 0.5s ease forwards ${index / 7 + 0.3}s`;
      }
    });
  });
}

// Fermer le menu mobile après avoir cliqué sur un lien
links.forEach(link => {
  link.addEventListener('click', () => {
    if (hamburger) hamburger.classList.remove('active');
    if (navLinks) navLinks.classList.remove('active');
    links.forEach(link => {
      link.style.animation = '';
    });
  });
});

// Menu de la documentation
const docNav = document.querySelector('.doc-nav');
const docSections = document.querySelectorAll('.doc-section');

// Mise en surbrillance du menu de navigation de la documentation
function highlightNav() {
  if (!docNav || !docSections.length) return;

  let current = '';
  let lastSection = null;

  docSections.forEach(section => {
    const sectionTop = section.offsetTop - 100;
    if (window.scrollY >= sectionTop) {
      current = '#' + section.getAttribute('id');
      lastSection = section;
    }
  });
  if ((window.innerHeight + window.scrollY) >= document.body.offsetHeight - 2 && lastSection) {
    current = '#' + lastSection.getAttribute('id');
  }

  docNav.querySelectorAll('a').forEach(link => {
    link.classList.remove('active');
    if (link.getAttribute('href') === current) {
      link.classList.add('active');
    }
  });
}

// Animation de défilement fluide pour les liens d'ancrage
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
  anchor.addEventListener('click', function (e) {
    e.preventDefault();
    
    const targetId = this.getAttribute('href');
    if (targetId === '#') return;
    
    const targetElement = document.querySelector(targetId);
    if (targetElement) {
      const headerOffset = 80;
      const elementPosition = targetElement.getBoundingClientRect().top;
      const offsetPosition = elementPosition + window.pageYOffset - headerOffset;
      
      window.scrollTo({
        top: offsetPosition,
        behavior: 'smooth'
      });
      
      // Fermer le menu mobile après le clic
      if (hamburger) hamburger.classList.remove('active');
      if (navLinks) navLinks.classList.remove('active');
    }
  });
});

// Animation au défilement
const animateOnScroll = () => {
  const elements = document.querySelectorAll('.feature-card, .hero-image img, .doc-section');
  
  elements.forEach(element => {
    const elementPosition = element.getBoundingClientRect().top;
    const screenPosition = window.innerHeight / 1.3;
    
    if (elementPosition < screenPosition) {
      element.style.opacity = '1';
      element.style.transform = 'translateY(0)';
    }
  });
  
  // Mettre à jour la navigation de la documentation
  highlightNav();
};

// Ajout d'un style pour les animations
const style = document.createElement('style');
style.textContent = `
  @keyframes navLinkFade {
    from {
      opacity: 0;
      transform: translateX(50px);
    }
    to {
      opacity: 1;
      transform: translateX(0);
    }
  }
  
  .feature-card, .doc-section {
    opacity: 0;
    transform: translateY(30px);
    transition: all 0.5s ease;
  }
  
  .hero-image img {
    opacity: 0;
    transform: translateY(30px);
    transition: all 0.8s ease 0.3s;
  }
  
  @keyframes fadeIn {
    from { opacity: 0; transform: translateY(20px); }
    to { opacity: 1; transform: translateY(0); }
  }
  
  .fade-in {
    opacity: 0;
  }
`;
document.head.appendChild(style);

// Gestion du menu de la documentation sur mobile
const docSidebar = document.querySelector('.doc-sidebar h3');
if (docSidebar && window.innerWidth <= 992) {
  docSidebar.addEventListener('click', () => {
    const nav = document.querySelector('.doc-nav');
    if (nav) nav.classList.toggle('active');
  });
}

// Écouteur d'événement pour l'animation au défilement
window.addEventListener('scroll', animateOnScroll);

// Animation initiale au chargement de la page
window.addEventListener('load', () => {
  // Afficher le contenu avec un léger délai pour l'animation
  document.body.style.opacity = '1';
  
  // Démarrer l'animation des éléments visibles
  animateOnScroll();
  
  // Activer le menu de la documentation si on est sur une ancre
  if (window.location.hash) {
    const target = document.querySelector(window.location.hash);
    if (target) {
      setTimeout(() => {
        target.scrollIntoView();
      }, 100);
    }
  }
});

// Effet de fondu au chargement de la page
document.body.style.transition = 'opacity 0.5s ease';
document.body.style.opacity = '0';


// Détection du thème du système
const prefersDarkScheme = window.matchMedia('(prefers-color-scheme: dark)');

// Fonction pour mettre à jour les icônes en fonction du thème
const updateThemeIcons = (isDark) => {
  const themeIcon = document.getElementById('theme-icon');
  if (themeIcon) {
    themeIcon.className = isDark ? 'fas fa-sun' : 'fas fa-moon';
  }
};

// Écouter les changements de thème
prefersDarkScheme.addListener((e) => {
  updateThemeIcons(e.matches);
});

// Initialiser les icônes au chargement
updateThemeIcons(prefersDarkScheme.matches);

// Faire apparaître progressivement les éléments au chargement
document.addEventListener('DOMContentLoaded', () => {
  const elements = document.querySelectorAll('.fade-in');
  elements.forEach((element, index) => {
    element.style.animation = `fadeIn 0.5s ease-out ${index * 0.1}s forwards`;
  });
  
  // Initialiser le menu de la documentation
  highlightNav();
});
